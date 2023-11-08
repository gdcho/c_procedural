#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char firstName[50];
    char lastName[50];
    char gpa[10];
    int toeflScore; // This will be ignored for domestic students
    char status;
} Student;

float getValidGPA(const char* gpaString) {
    char* end;
    double val = strtod(gpaString, &end);
    if (end == gpaString || *end != '\0' || val < 0.0) {
        return -1.0f;
    }
    const char* decimalPoint = strchr(gpaString, '.');
    if (decimalPoint != NULL) {
        int decimalPlaces = strlen(decimalPoint + 1);
        if (decimalPlaces > 3) {
            return -1.0f;
        }
    }
    return (float)val;
}

int isValidTOEFLScore(int score) {
    return score >= 0 && score <= 120;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Error: Incorrect number of arguments. Usage: %s <input file> <output file> <option>\n", argv[0]);
        return 1;
    }

    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL) {
        printf("Error: Could not open input file '%s'\n", argv[1]);
        return 1;
    }

    FILE *outfile = fopen(argv[2], "w");
    if (outfile == NULL) {
        fclose(infile);
        printf("Error: Could not open output file '%s'\n", argv[2]);
        return 1;
    }

    int option = atoi(argv[3]);
    if (option < 1 || option > 3) {
        fprintf(outfile, "Error: Option must be 1, 2, or 3\n");
        fclose(infile);
        fclose(outfile);
        return 1;
    }

    Student *students = NULL;
    int studentsCount = 0;
    int studentsSize = 0;

    char line[200];
    while (fgets(line, sizeof(line), infile)) {
        Student tempStudent;
        int toeflScore = 0; // Default TOEFL score
        int fields = sscanf(line, "%49s %49s %9s %c %d", tempStudent.firstName, tempStudent.lastName, tempStudent.gpa, &tempStudent.status, &toeflScore);

        tempStudent.status = toupper((unsigned char)tempStudent.status);

        if ((tempStudent.status == 'D' && fields < 3) || (tempStudent.status == 'I' && fields < 5)) {
            fprintf(outfile, "Error: Incorrect format or missing fields: %s", line);
            continue;
        }

        float gpa = getValidGPA(tempStudent.gpa);
        if (gpa < 0.0f) {
            fprintf(outfile, "Error: Invalid GPA format for student: %s", line);
            continue;
        }

        if (gpa <= 3.9f) {
            continue;
        }

        if (tempStudent.status == 'I') {
            if (!isValidTOEFLScore(toeflScore)) {
                fprintf(outfile, "Error: Invalid TOEFL score for international student: %s", line);
                continue;
            }

            if (toeflScore < 70 && option != 3) {
                continue;
            }
        }

        if (studentsCount >= studentsSize) {
            studentsSize = studentsSize > 0 ? studentsSize * 2 : 1;
            Student* temp = realloc(students, studentsSize * sizeof(Student));
            if (temp == NULL) {
                fprintf(outfile, "Error: Memory allocation failed.\n");
                free(students);
                fclose(infile);
                fclose(outfile);
                return 1;
            }
            students = temp;
        }

        strcpy(students[studentsCount].firstName, tempStudent.firstName);
        strcpy(students[studentsCount].lastName, tempStudent.lastName);
        strcpy(students[studentsCount].gpa, tempStudent.gpa);
        students[studentsCount].toeflScore = toeflScore;
        students[studentsCount].status = tempStudent.status;
        studentsCount++;
    }

    for (int i = 0; i < studentsCount; i++) {
        if ((students[i].status == 'D' && option != 2) || (students[i].status == 'I' && option != 1)) {
            if (students[i].status == 'D') {
                fprintf(outfile, "%s %s %s D\n", students[i].firstName, students[i].lastName, students[i].gpa);
            } else {
                fprintf(outfile, "%s %s %s I %d\n", students[i].firstName, students[i].lastName, students[i].gpa, students[i].toeflScore);
            }
        }
    }

    free(students);
    fclose(infile);
    fclose(outfile);

    return 0;
}
