#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    INT, FLOAT, CHAR, DOUBLE, VOID_PTR
} DataType;

typedef struct Node {
    void *key;
    size_t keySize;
    DataType keyType;
    void *value;
    size_t valueSize;
    DataType valueType;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} DoublyLinkedList;

DoublyLinkedList* createList() {
    DoublyLinkedList *list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
    if (!list) {
        fprintf(stderr, "Failed to allocate memory for list.\n");
        exit(1);
    }
    list->head = list->tail = NULL;
    return list;
}

void insertKeyValue(DoublyLinkedList *list, void *key, size_t keySize, DataType keyType, void *value, size_t valueSize, DataType valueType) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Failed to allocate memory for node.\n");
        exit(1);
    }

    newNode->key = malloc(keySize);
    if (!newNode->key) {
        free(newNode);
        fprintf(stderr, "Failed to allocate memory for key.\n");
        exit(1);
    }
    memcpy(newNode->key, key, keySize);
    newNode->keySize = keySize;
    newNode->keyType = keyType;

    newNode->value = malloc(valueSize);
    if (!newNode->value) {
        free(newNode->key);
        free(newNode);
        fprintf(stderr, "Failed to allocate memory for value.\n");
        exit(1);
    }
    memcpy(newNode->value, value, valueSize);
    newNode->valueSize = valueSize;
    newNode->valueType = valueType;

    newNode->next = NULL;
    if (list->tail) {
        list->tail->next = newNode;
        newNode->prev = list->tail;
    } else {
        list->head = newNode;
        newNode->prev = NULL;
    }
    list->tail = newNode;
}

void printData(void *data, DataType type) {
    switch (type) {
        case INT:
            printf("INT: %d\n", *(int *)data);
            break;
        case FLOAT:
            printf("FLOAT: %f\n", *(float *)data);
            break;
        case CHAR:
            printf("CHAR: %c\n", *(char *)data);
            break;
        case DOUBLE:
            printf("DOUBLE: %lf\n", *(double *)data);
            break;
        case VOID_PTR:
            printf("VOID_PTR: %p\n", data);
            break;
        default:
            printf("Unknown type.\n");
    }
}

void printKeys(const DoublyLinkedList *list) {
    Node *current = list->head;
    while (current) {
        printData(current->key, current->keyType);
        current = current->next;
    }
}

void printValues(const DoublyLinkedList *list) {
    Node *current = list->head;
    while (current) {
        printData(current->value, current->valueType);
        current = current->next;
    }
}

DataType getDataType() {
    int type;
    printf("Choose data type (0: INT, 1: FLOAT, 2: CHAR, 3: DOUBLE, 4: VOID_PTR): ");
    scanf("%d", &type);
    while (getchar() != '\n');  // Clear the input buffer
    return (DataType)type;
}

void *readData(DataType type, size_t *size) {
    void *data;
    printf("Enter data size in bytes: ");
    scanf("%zu", size);
    data = malloc(*size);

    switch (type) {
        case INT:
            printf("Enter an integer: ");
            scanf("%d", (int *)data);
            break;
        case FLOAT:
            printf("Enter a float: ");
            scanf("%f", (float *)data);
            break;
        case CHAR:
            printf("Enter a character: ");
            while (getchar() != '\n');
            scanf("%c", (char *)data);
            break;
        case DOUBLE:
            printf("Enter a double: ");
            scanf("%lf", (double *)data);
            break;
        case VOID_PTR:
            printf("Enter an integer for void pointer: ");
            scanf("%d", (int *)data);
            break;
        default:
            printf("Unknown data type.\n");
            data = NULL;
    }
    while (getchar() != '\n');
    return data;
}

void handleInsertKeyValue(DoublyLinkedList *list) {
    size_t keySize, valueSize;
    DataType keyType, valueType;
    void *key, *value;

    printf("Insert key:\n");
    keyType = getDataType();
    key = readData(keyType, &keySize);

    printf("Insert value:\n");
    valueType = getDataType();
    value = readData(valueType, &valueSize);

    if (key && value) {
        insertKeyValue(list, key, keySize, keyType, value, valueSize, valueType);
    } else {
        printf("Error in key or value input.\n");
        if (key) free(key);
        if (value) free(value);
    }
}

void saveToFile(const DoublyLinkedList *list, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        fprintf(stderr, "Failed to open file for writing.\n");
        return;
    }

    Node *current = list->head;
    while (current) {
        fwrite(&(current->keySize), sizeof(size_t), 1, file);
        fwrite(&(current->keyType), sizeof(DataType), 1, file);
        fwrite(current->key, current->keySize, 1, file);
        fwrite(&(current->valueSize), sizeof(size_t), 1, file);
        fwrite(&(current->valueType), sizeof(DataType), 1, file);
        fwrite(current->value, current->valueSize, 1, file);
        current = current->next;
    }

    fclose(file);
}

void clearList(DoublyLinkedList *list) {
    Node *current = list->head;
    while (current) {
        Node *temp = current;
        current = current->next;
        free(temp->key);
        free(temp->value);
        free(temp);
    }
    list->head = list->tail = NULL;
}

void restoreFromFile(DoublyLinkedList *list, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Failed to open file for reading.\n");
        return;
    }

    clearList(list);

    size_t keySize, valueSize;
    DataType keyType, valueType;
    void *key, *value;

    while (fread(&keySize, sizeof(size_t), 1, file)) {
        fread(&keyType, sizeof(DataType), 1, file);
        key = malloc(keySize);
        fread(key, keySize, 1, file);
        fread(&valueSize, sizeof(size_t), 1, file);
        fread(&valueType, sizeof(DataType), 1, file);
        value = malloc(valueSize);
        fread(value, valueSize, 1, file);
        insertKeyValue(list, key, keySize, keyType, value, valueSize, valueType);
        free(key);
        free(value);
    }

    fclose(file);
}

void freeList(DoublyLinkedList *list) {
    clearList(list);
    free(list);
}

void displayMenu() {
    printf("1) Print Keys\n");
    printf("2) Print Values\n");
    printf("3) Insert KV Pair\n");
    printf("4) Save\n");
    printf("5) Restore\n");
    printf("6) Exit\n");
    printf("Enter your choice: ");
}

int main() {
    DoublyLinkedList *list = createList();
    char filename[100];
    int choice;

    while (1) {
        displayMenu();
        scanf("%d", &choice);
        while (getchar() != '\n');  // Clear the input buffer

        switch (choice) {
            case 1: // Print Keys
                printKeys(list);
                break;
            case 2: // Print Values
                printValues(list);
                break;
            case 3: // Insert KV Pair
                handleInsertKeyValue(list);
                break;
            case 4: // Save
                printf("Type the file name: ");
                scanf("%s", filename);
                saveToFile(list, filename);
                break;
            case 5: // Restore
                printf("Type the file name: ");
                scanf("%s", filename);
                restoreFromFile(list, filename);
                break;
            case 6: // Exit
                freeList(list);
                return 0;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}
