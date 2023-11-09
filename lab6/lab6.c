#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char firstName[50];
    char lastName[50];
    char gpa[10];
} DomesticStudent;

typedef struct {
    char firstName[50];
    char lastName[50];
    char gpa[10];
    int toeflScore;
} InternationalStudent;

float getValidGPA(const char* gpaString) {
    char* end;
    float val = strtof(gpaString, &end);
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
    return val;
}

int isValidTOEFLScore(int score) {
    return score >= 70 && score <= 120;
}

int isTOEFLScoreInRange(int score) {
    return score >= 0 && score <= 120;
}

void writeStudent(FILE *outfile, const char *firstName, const char *lastName, const char *gpa, char status, int toeflScore) {
    if (status == 'I') {
        fprintf(outfile, "%s %s %s I %d\n", firstName, lastName, gpa, toeflScore);
    } else {
        fprintf(outfile, "%s %s %s D\n", firstName, lastName, gpa);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Error: Incorrect number of arguments. Usage: %s <input file> <output file> <option>\n", argv[0]);
        return 1;
    }

    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL) {
        fprintf(stderr, "Error: Could not open input file '%s'\n", argv[1]);
        return 1;
    }

    FILE *outfile = fopen(argv[2], "w");
    if (outfile == NULL) {
        fclose(infile);
        fprintf(stderr, "Error: Could not open output file '%s'\n", argv[2]);
        return 1;
    }

    int option = atoi(argv[3]);
    if (option < 1 || option > 3) {
        fprintf(outfile, "Error: Option must be 1, 2, or 3\n");
        fclose(infile);
        fclose(outfile);
        return 1;
    }

    char line[200];
    while (fgets(line, sizeof(line), infile)) {
        char firstName[50], lastName[50], gpa[10], status;
        int toeflScore;
        int fields = sscanf(line, "%49s %49s %9s %c %d", firstName, lastName, gpa, &status, &toeflScore);

        if (fields < 4 || (status == 'I' && fields != 5)) {
            fprintf(outfile, "Error: Incorrect format in line: %s", line);
            continue;
        }

        status = toupper((unsigned char)status);
        float gpaVal = getValidGPA(gpa);

        if (gpaVal < 0.0f) {
            fprintf(outfile, "Error: Invalid GPA format: %s", line);
            continue;
        }

        if (gpaVal <= 3.9f) {
            continue;
        }

        if (status == 'D' && (option == 1 || option == 3)) {
            writeStudent(outfile, firstName, lastName, gpa, 'D', 0);
        } else if (status == 'I' && (option == 2 || option == 3)) {
            if (fields == 5 && !isTOEFLScoreInRange(toeflScore)) {
                fprintf(outfile, "Error: Invalid TOEFL score format: %s", line);
                continue;
            }
            if (isValidTOEFLScore(toeflScore)) {
                writeStudent(outfile, firstName, lastName, gpa, 'I', toeflScore);
            }
        }
    }

    fclose(infile);
    fclose(outfile);

    return 0;
}
