#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    char firstName[50];
    char lastName[50];
    char studentNumber[9];
    int midtermGrade;
    int finalGrade;
} Student;

int calculateAverage(Student student) {
    float average = (student.midtermGrade + student.finalGrade) / 2.0f;
    return (int)round(average);
}

int compareStudents(const void *a, const void *b) {
    const Student *studentA = (const Student *)a;
    const Student *studentB = (const Student *)b;

    int lastNameComparison = strcmp(studentA->lastName, studentB->lastName);
    if (lastNameComparison != 0) return lastNameComparison;

    int firstNameComparison = strcmp(studentA->firstName, studentB->firstName);
    if (firstNameComparison != 0) return firstNameComparison;

    int studentNumberComparison = strcmp(studentA->studentNumber, studentB->studentNumber);
    if (studentNumberComparison != 0) return studentNumberComparison;

    if (studentA->midtermGrade != studentB->midtermGrade)
        return studentA->midtermGrade - studentB->midtermGrade;

    return studentA->finalGrade - studentB->finalGrade;
}

void swap(Student *a, Student *b) {
    Student t = *a;
    *a = *b;
    *b = t;
}

int partition(Student arr[], int low, int high) {
    Student pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (compareStudents(&arr[j], &pivot) < 0) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSortStudents(Student arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortStudents(arr, low, pi - 1);
        quickSortStudents(arr, pi + 1, high);
    }
}

void writeOutputFile(Student students[], int studentCount, const char* filename, int option) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < studentCount; i++) {
        int average = calculateAverage(students[i]);

        if ((option == 1 && average > 90 && average <= 100) ||
            (option == 2 && average > 80 && average <= 90) ||
            (option == 3 && average > 70 && average <= 80) ||
            (option == 4 && average > 60 && average <= 70) ||
            (option == 5 && average <= 60)) {
            fprintf(file, "%s %s %s %d %d\n",
                    students[i].firstName, students[i].lastName, students[i].studentNumber,
                    students[i].midtermGrade, students[i].finalGrade);
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <input file> <output file> <option>\n", argv[0]);
        return 1;
    }

    const char *inputFileName = argv[1];
    const char *outputFileName = argv[2];
    int option = atoi(argv[3]);

    if (option < 1 || option > 5) {
        printf("Invalid option. Option must be between 1 and 5\n");
        return 1;
    }

    FILE *inputFile = fopen(inputFileName, "r");
    if (!inputFile) {
        perror("Error opening input file");
        return 1;
    }

    int n = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), inputFile)) {
        n++;
    }
    rewind(inputFile);

    Student *students = (Student *)malloc(n * sizeof(Student));
    if (!students) {
        perror("Failed to allocate memory for students");
        fclose(inputFile);
        return 1;
    }

    for (int i = 0; i < n && !feof(inputFile); i++) {
        fscanf(inputFile, "%s %s %s %d %d",
               students[i].firstName, students[i].lastName,
               students[i].studentNumber, &students[i].midtermGrade,
               &students[i].finalGrade);
    }
    fclose(inputFile);

    quickSortStudents(students, 0, n - 1);

    writeOutputFile(students, n, outputFileName, option);

    free(students);

    return 0;
}
