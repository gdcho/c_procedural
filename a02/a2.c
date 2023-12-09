#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student
{
    char firstName[50];
    char lastName[50];
    char monthOfBirth[3];
    int dayOfBirth;
    int yearOfBirth;
    char gpa[6];
    char status;
    int toefl;
} Student;

int dayValidator(int day, int month, int year)
{
    if (month == 1 || month == 3 || month == 5 || month == 7 ||
        month == 8 || month == 10 || month == 12)
    {
        if (day < 1 || day > 31)
        {
            return 0;
        }
    }

    if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day < 1 || day > 30)
        {
            return 0;
        }
    }
    else if (month == 2)
    {
        if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
        {
            if (day < 1 || day > 29)
            {
                return 0;
            }
        }
        else
        {
            if (day < 1 || day > 28)
            {
                return 0;
            }
        }
    }
    return 1;
}

int intOfMonth(const char *stringMonth)
{
    static const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                   "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    for (int i = 0; i < 12; i++)
    {
        if (strcmp(stringMonth, months[i]) == 0)
        {
            return i + 1;
        }
    }
    return 0;
}

int compare(Student *a, Student *b)
{
    int aYear = a->yearOfBirth;
    int aMonth = intOfMonth(a->monthOfBirth);
    int aDay = a->dayOfBirth;

    int bYear = b->yearOfBirth;
    int bMonth = intOfMonth(b->monthOfBirth);
    int bDay = b->dayOfBirth;

    if (aYear != bYear)
    {
        return aYear - bYear;
    }

    if (aMonth != bMonth)
    {
        return aMonth - bMonth;
    }

    if (aDay != bDay)
    {
        if (dayValidator(aDay, aMonth, aYear) &&
            dayValidator(bDay, bMonth, bYear))
        {
            return aDay - bDay;
        }
    }

    int compareLastName = strcasecmp(a->lastName, b->lastName);

    if (compareLastName != 0)
    {
        return compareLastName;
    }

    int compareFirstName = strcasecmp(a->firstName, b->firstName);
    if (compareFirstName != 0)
    {
        return compareFirstName;
    }

    int compareGPA = strcasecmp(a->gpa, b->gpa);
    if (compareGPA != 0)
    {
        return compareGPA;
    }

    int compareStatus = strcasecmp(&a->status, &b->status);
    if (compareStatus != 0)
    {
        return compareStatus;
    }

    int aToefl = a->toefl;
    int bToefl = b->toefl;

    if (aToefl != bToefl)
    {
        return aToefl - bToefl;
    }

    return 0;
}

Student *divide(Student *arr, int start, int end)
{
    int size = end - start + 1;
    Student *tempArr = (Student *)malloc(size * sizeof(Student));

    for (int i = 0; i < size; i++)
    {
        tempArr[i] = arr[start + i];
    }

    return tempArr;
}

void conquer(Student *arr, Student *leftArr, int leftSize, Student *rightArr, int rightSize, int start)
{
    int i = 0;
    int j = 0;
    int k = start;

    while (i < leftSize || j < rightSize)
    {
        if (j >= rightSize || (i < leftSize && compare(&leftArr[i], &rightArr[j]) <= 0))
        {
            arr[k++] = leftArr[i++];
        }
        else
        {
            arr[k++] = rightArr[j++];
        }
    }
}

void mergeSort(Student *arr, int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;

        int leftSize = middle - left + 1;
        int rightSize = right - middle;

        Student *leftArr = divide(arr, left, middle);
        Student *rightArr = divide(arr, middle + 1, right);

        mergeSort(leftArr, 0, leftSize - 1);
        mergeSort(rightArr, 0, rightSize - 1);

        conquer(arr, leftArr, leftSize, rightArr, rightSize, left);

        free(leftArr);
        free(rightArr);
    }
}

int readInputFile(const char *inputFile, const char *outputFile, Student **students)
{
    FILE *inputFilePtr = fopen(inputFile, "r");
    FILE *outputFilePtr = fopen(outputFile, "w");

    if (inputFilePtr == NULL)
    {
        printf("Error: Cannot open file.\n");
        exit(1);
    }

    Student *tempStudents = NULL;
    int lines = 0;
    int size = 8;
    tempStudents = (Student *)malloc(sizeof(Student) * size);

    int i = 0;

    while (fscanf(inputFilePtr, "%s %s %3s-%d-%d %s %c", tempStudents[i].firstName, tempStudents[i].lastName,
                  tempStudents[i].monthOfBirth, &tempStudents[i].dayOfBirth, &tempStudents[i].yearOfBirth,
                  tempStudents[i].gpa, &tempStudents[i].status) != EOF)
    {
        if (tempStudents[i].status == 'I')
        {
            if (fscanf(inputFilePtr, "%d", &tempStudents[i].toefl) != 1)
            {
                fprintf(outputFilePtr, "Error: Invalid or insufficient toefl score for international student: %s %s\n",
                        tempStudents[i].firstName, tempStudents[i].lastName);
                exit(1);
            }
            if (tempStudents[i].toefl < 0 || tempStudents[i].toefl > 120)
            {
                fprintf(outputFilePtr, "Error: Toefl score should range 0 to 120: %d\n", tempStudents[i].toefl);
                exit(1);
            }
        }

        if (tempStudents[i].status == 'D')
        {
            if (fscanf(inputFilePtr, "%d", &tempStudents[i].toefl) == 1)
            {
                fprintf(outputFilePtr, "Error: Toefl field should not be given for domestic student: %s %s\n",
                        tempStudents[i].firstName, tempStudents[i].lastName);
                exit(1);
            }
        }

        if (tempStudents[i].yearOfBirth < 1950 || tempStudents[i].yearOfBirth > 2010)
        {
            fprintf(outputFilePtr, "Error: Invalid or insufficient birthdate for student: %s %s\n",
                    tempStudents[i].firstName, tempStudents[i].lastName);
            exit(1);
        }

        if (intOfMonth(tempStudents[i].monthOfBirth) == 0)
        {
            fprintf(outputFilePtr, "Error: Invalid or insufficient birthdate for student: %s %s\n",
                    tempStudents[i].firstName, tempStudents[i].lastName);
            exit(1);
        }

        int a = dayValidator(tempStudents[i].dayOfBirth,
                             intOfMonth(tempStudents[i].monthOfBirth),
                             tempStudents[i].yearOfBirth);

        if (tempStudents[i].status == 'D' && tempStudents[i].toefl != 0)
        {
            fprintf(outputFilePtr, "Error: Invalid or insufficient birthdate for student: %s %s\n",
                    tempStudents[i].firstName, tempStudents[i].lastName);
            exit(1);
        }

        if (tempStudents[i].status != 'D' && tempStudents[i].status != 'I')
        {
            fprintf(outputFilePtr, "Error: Invalid or insufficient details for student: %s %s\n",
                    tempStudents[i].firstName, tempStudents[i].lastName);
            exit(1);
        }

        if (a != 1)
        {
            fprintf(outputFilePtr, "Error: Invalid or insufficient birthdate for student: %s %s\n",
                    tempStudents[i].firstName, tempStudents[i].lastName);
            exit(1);
        }

        if (atof(tempStudents[i].gpa) < 0 || atof(tempStudents[i].gpa) > 4.3)
        {
            fprintf(outputFilePtr, "Error: Invalid or insufficient GPA Information: %s\n", tempStudents[i].gpa);
            exit(1);
        }

        i++;
        lines++;

        if (lines == size)
        {
            size *= 2;
            tempStudents = (Student *)realloc(tempStudents, sizeof(Student) * size);
        }
    }

    *students = (Student *)malloc(sizeof(Student) * lines);

    for (int i = 0; i < lines; i++)
    {
        (*students)[i] = tempStudents[i];
    }

    free(tempStudents);

    fclose(inputFilePtr);
    fclose(outputFilePtr);

    return lines;
}

void writeOutputFile(const char *outputFile, Student *students, int n, int option)
{
    FILE *outputFilePtr = fopen(outputFile, "w");

    if (outputFilePtr == NULL)
    {
        printf("Error: Cannot open file.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        if (option == 1 && students[i].status == 'D')
        {
            fprintf(outputFilePtr, "%s %s %3s-%d-%d %s %c\n", students[i].firstName, students[i].lastName,
                    students[i].monthOfBirth, students[i].dayOfBirth, students[i].yearOfBirth,
                    students[i].gpa, students[i].status);
        }
        else if (option == 2 && students[i].status == 'I')
        {
            fprintf(outputFilePtr, "%s %s %3s-%d-%d %s %c %d\n", students[i].firstName, students[i].lastName,
                    students[i].monthOfBirth, students[i].dayOfBirth, students[i].yearOfBirth,
                    students[i].gpa, students[i].status, students[i].toefl);
        }
        else if (option == 3)
        {
            if (students[i].status == 'D')
            {
                fprintf(outputFilePtr, "%s %s %3s-%d-%d %s %c\n", students[i].firstName, students[i].lastName,
                        students[i].monthOfBirth, students[i].dayOfBirth, students[i].yearOfBirth,
                        students[i].gpa, students[i].status);
            }
            else if (students[i].status == 'I')
            {
                fprintf(outputFilePtr, "%s %s %3s-%d-%d %s %c %d\n", students[i].firstName, students[i].lastName,
                        students[i].monthOfBirth, students[i].dayOfBirth, students[i].yearOfBirth,
                        students[i].gpa, students[i].status, students[i].toefl);
            }
        }
    }

    fclose(outputFilePtr);
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s <input file> <output file> <option>\n", argv[0]);
        return 1;
    }
    const char *inputFile = argv[1];
    const char *outputFile = argv[2];
    int option = atoi(argv[3]);
    if (option < 1 || option > 3) {
        printf("Error: Option must be 1, 2, or 3\n");
        return 1;
    }

    Student *students = NULL;

    int n = readInputFile(inputFile, outputFile, &students);

    mergeSort(students, 0, n - 1);

    writeOutputFile(outputFile, students, n, option);

    free(students);

    return 0;
}
