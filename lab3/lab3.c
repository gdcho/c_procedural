#include <stdio.h>
#include <stdlib.h>

// Function to rotate a 2D array by a given angle (in degrees)
void rotateArray(char **arr, int n, int rows, int cols) {
    int degrees = (n/90);
    int rotations = degrees % 4;
    int rotation = 0;

    while (rotation < rotations) {
        // tempArry pointer to type char for arr elements
        // malloc to allocate memory for array of char pointers
        char **rotatedArr = (char **)malloc(rows * sizeof(char *));
        int i = 0;
        while (i < rows) {
            rotatedArr[i] = (char *)malloc(cols * sizeof(char)); // indexed based on i iterations and memory allocations
            int j = 0;
            while (j < cols) {
                rotatedArr[i][j] = arr[cols - 1 - j][i]; // store rotated values back 
                j++;
            }
            i++;
        }

        i = 0;
        while (i < rows) {
            int j = 0;
            while (j < cols) {
                arr[i][j] = rotatedArr[i][j];
                j++;
            }
            free(rotatedArr[i]);
            i++;
        }
        free(rotatedArr);
        rotation++;
    }
}

// Function to zoom (expand or shrink) a 2D array by a given factor
void zoomArray(char **arr, double zoomFactor, int *rows, int *cols) {
    // new calculated dimensions for columns and rows by zoomFactor
    int newRows = (int)(*rows * zoomFactor + 0.5);
    int newCols = (int)(*cols * zoomFactor + 0.5);
    
    // allocate memory into tempArr
    // tempArr created with pointer to type char and based on newRows
    char **resizedArr = (char **)malloc(newRows * sizeof(char *));
    
    int i = 0;
    while (i < newRows) {
        // pointer to type char for inner array for columns based on newCols
        resizedArr[i] = (char *)malloc(newCols * sizeof(char));
        int j = 0;
        while (j < newCols) {
            // map back to the original array
            int origRow = (int)(i / zoomFactor);
            int origCol = (int)(j / zoomFactor);
            // mapped values to be stored in resizedArr
            resizedArr[i][j] = arr[origRow][origCol];
            j++;
        }
        i++;
    }

    i = 0;
    while (i < newRows) {
        int j = 0;
        while (j < newCols) {
            arr[i][j] = resizedArr[i][j]; // copy back to original array
            j++;
        }
        free(resizedArr[i]);
        i++;
    }
    free(resizedArr);
    // update the dimensions in the original pointers
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
