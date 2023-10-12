#include <stdio.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_CHAR_PER_LINE 256

// Recursive function to reverse a string
void reverseString(char* start, char* end) {
    if (start >= end)
        return;

    char temp = *start;
    *start = *end;
    *end = temp;

    reverseString(start + 1, end - 1);
}

// Recursive function to print reversed lines
void reverseLines(FILE *file, int current_line) {
    if (current_line >= MAX_LINES)
        return;

    char line[MAX_CHAR_PER_LINE];
    if (fgets(line, MAX_CHAR_PER_LINE, file) == NULL)
        return;

    reverseLines(file, current_line + 1); // Process next line

    // Reverse and print current line
    line[strcspn(line, "\n")] = 0; // Remove the trailing newline
    reverseString(line, line + strlen(line) - 1); 
    printf("%s\n", line);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 2;
    }

    reverseLines(file, 0);

    fclose(file);
    return 0;
}
