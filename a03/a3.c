#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char *firstName;
    char *lastName;
    struct Node *left, *right;
} Node;

Node *createNode(char *firstName, char *lastName)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->firstName = (char *)malloc((strlen(firstName) + 1) * sizeof(char));
    newNode->lastName = (char *)malloc((strlen(lastName) + 1) * sizeof(char));

    strcpy(newNode->firstName, firstName);
    strcpy(newNode->lastName, lastName);

    newNode->left = newNode->right = NULL;

    return newNode;
}

int compareNames(char *firstName1, char *lastName1, char *firstName2, char *lastName2)
{
    int firstCompare = strcmp(firstName1, firstName2);
    if (firstCompare == 0)
    {
        return strcmp(lastName1, lastName2);
    }
    return firstCompare;
}

Node *addNode(Node *root, char *firstName, char *lastName)
{
    if (root == NULL)
    {
        return createNode(firstName, lastName);
    }

    if (compareNames(firstName, lastName, root->firstName, root->lastName) <= 0)
    {
        root->left = addNode(root->left, firstName, lastName);
    }
    else
    {
        root->right = addNode(root->right, firstName, lastName);
    }

    return root;
}

Node *findMinimum(Node *root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

Node *deleteNode(Node *root, char *firstName, char *lastName)
{
    if (root == NULL)
    {
        return createNode(firstName, lastName);
    }

    int cmp = compareNames(firstName, lastName, root->firstName, root->lastName);
    if (cmp < 0)
    {
        root->left = deleteNode(root->left, firstName, lastName);
    }
    else if (cmp > 0)
    {
        root->right = deleteNode(root->right, firstName, lastName);
    }
    else
    {
        if (root->left == NULL)
        {
            Node *temp = root->right;
            free(root->firstName);
            free(root->lastName);
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            Node *temp = root->left;
            free(root->firstName);
            free(root->lastName);
            free(root);
            return temp;
        }

        Node *temp = findMinimum(root->right);

        strcpy(root->firstName, temp->firstName);
        strcpy(root->lastName, temp->lastName);

        root->right = deleteNode(root->right, temp->firstName, temp->lastName);
    }
    return root;
}

void searchNode(Node *root, char *firstName, char *lastName, FILE *outputFile)
{
    if (root == NULL)
    {
        fprintf(outputFile, "Not Found\n");
        return;
    }

    int cmp = compareNames(firstName, lastName, root->firstName, root->lastName);
    if (cmp < 0)
    {
        searchNode(root->left, firstName, lastName, outputFile);
    }
    else if (cmp > 0)
    {
        searchNode(root->right, firstName, lastName, outputFile);
    }
    else
    {
        fprintf(outputFile, "Found\n");
    }
}

void inOrderTraversal(Node *root, FILE *outputFile)
{
    if (root != NULL)
    {
        inOrderTraversal(root->left, outputFile);
        fprintf(outputFile, "%s %s\n", root->firstName, root->lastName);
        inOrderTraversal(root->right, outputFile);
    }
}

void freeTree(Node *root)
{
    if (root != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root->firstName);
        free(root->lastName);
        free(root);
    }
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        return 1;
    }

    FILE *inputFile, *outputTxtFile;

    inputFile = fopen(argv[1], "r");
    outputTxtFile = fopen(argv[2], "w");

    // A numbers of everyone. AXXXX_AXXXX_AXXX format.
    char *ANum = "A01345231_A01351217_A01347599";

    FILE *outputFile = fopen(ANum, "w");

    if (outputFile == NULL)
    {
        printf("Failed to create the output file.\n");
        return 1;
    }

    fclose(outputFile);

    if (!inputFile || !outputTxtFile)
    {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    Node *root = NULL;
    char *firstName, *lastName;
    int operation;

    int firstNameSize = 32;
    int lastNameSize = 32;

    firstName = (char *)malloc(firstNameSize * sizeof(char));
    lastName = (char *)malloc(lastNameSize * sizeof(char));

    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;

    while ((linelen = getline(&line, &linecap, inputFile)) != -1)
    {
        if (strlen(line) >= firstNameSize || strlen(line) >= lastNameSize)
        {
            firstNameSize = strlen(line);
            lastNameSize = strlen(line);

            firstName = (char *)realloc(firstName, firstNameSize * sizeof(char));
            lastName = (char *)realloc(lastName, lastNameSize * sizeof(char));

            if (!firstName || !lastName)
            {
                fprintf(stderr, "Memory allocation failed\n");
                return 1;
            }
        }

        int numTokens = sscanf(line, "%s %s %d", firstName, lastName, &operation);

        switch (numTokens)
        {
            case 1:
                inOrderTraversal(root, outputTxtFile);
                break;

            case 3:
                switch (operation)
                {
                    case 1:
                        root = addNode(root, firstName, lastName);
                        break;
                    case 2:
                        root = deleteNode(root, firstName, lastName);
                        break;
                    case 3:
                        searchNode(root, firstName, lastName, outputTxtFile);
                        break;
                }
                break;

            default:
                fprintf(outputTxtFile, "Error\n");
                break;
        }
    }

    fclose(inputFile);
    fclose(outputTxtFile);
    freeTree(root);

    free(firstName);
    free(lastName);
    free(line);

    return 0;
}
