#include <stdio.h>
#include <stdlib.h>

// Function to rotate a 2D array by a given angle (in degrees)
void rotateArray(char **arr, int n, int rows, int cols)
{
    int degrees = (n/90);
    int rotations = degrees % 4;

    for (int i = 0; i < rotations; i++) {
        char **tempArr = (char **)malloc(rows * sizeof(char *));
        for (int j = 0; j < rows; j++) {
            tempArr[j] = (char *)malloc(cols * sizeof(char));
            for (int k = 0; k < cols; k++) {
                tempArr[j][k] = arr[j][k];
            }
        }

        for (int j = 0; j < rows; j++) {
            for (int k = 0; k < cols; k++) {
                arr[k][rows - 1 - j] = tempArr[j][k];
            }
            free(tempArr[j]);
        }
        free(tempArr);
    }
}

// Function to zoom (expand or shrink) a 2D array by a given factor
void zoomArray(char **arr, double zoomFactor, int *rows, int *cols) {
    int newRows = (int)(*rows * zoomFactor + 0.5);
    int newCols = (int)(*cols * zoomFactor + 0.5);

    char **tempArr = (char **)malloc(newRows * sizeof(char *));
    for (int i = 0; i < newRows; i++) {
        tempArr[i] = (char *)malloc(newCols * sizeof(char));
        for (int j = 0; j < newCols; j++) {
            int origR = (int)(i / zoomFactor);
            int origC = (int)(j / zoomFactor);
            tempArr[i][j] = arr[origR][origC];
        }
    }
    for (int i = 0; i < newRows; i++) {
        for (int j = 0; j < newCols; j++) {
            arr[i][j] = tempArr[i][j];
        }
        free(tempArr[i]);
    }
    free(tempArr);
    *rows = newRows;
    *cols = newCols;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <input_file> <angle_degrees> <zoom_factor>\n", argv[0]);
        return 1;
    }

    char *inputFileName = argv[1];
    int angle = atoi(argv[2]);
    double zoomFactor = atof(argv[3]); // Use atof to convert the zoom factor to a double

    // Initialize a 2D array of size 30x30 as a pointer-to-pointer
    char **arr = (char **)malloc(30 * sizeof(char *));
    for (int i = 0; i < 30; i++) {
        arr[i] = (char *)malloc(30 * sizeof(char));
    }

    // Open the input file for reading
    FILE *file = fopen(inputFileName, "r");
    if (file == NULL) {
        printf("Failed to open the input file.\n");
        return 1;
    }

    // Read the input array from the specified file and populate arr
    int rows = 0;
    int cols = 0;
    char c;

    while (rows < 30 && cols < 30 && fscanf(file, "%c", &arr[rows][cols]) == 1) {
        if (arr[rows][cols] == '\n') {
          rows++;
          cols = 0;
        } else {
          cols++;
        }
    }
    cols = rows;
    
    // Close the input file
    fclose(file);

    // Print the array
    printf("Input Array:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          printf("%c ", arr[i][j]);
        }
        printf("\n");
    }

    
    // Call rotateArray or zoomArray based on the angle and zoomFactor
    // For example:
    rotateArray(arr, angle, rows, cols);
    zoomArray(arr, zoomFactor, &rows, &cols);

    // Print the array
    printf("Output %dx%d Array:\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          printf("%c ", arr[i][j]);
        }
        printf("\n");
    }

    // Free dynamically allocated memory when done
    for (int i = 0; i < 30; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}
