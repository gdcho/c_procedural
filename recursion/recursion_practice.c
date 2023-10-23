#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int sum_numbers(int n){
    if (n == 1) {
        return 1;
    } else {
        return n + sum_numbers(n-1);
    }
}

void fibonacci_sq(int term) {
    static int prNo = 0;
    static int num = 1;
    static int i = 0;

    if (i >= term) { // reset static variables
            prNo = 0;
            num = 1;
            i = 0;
        return;
    }

    if (i == 0) {
        printf("%d, ", prNo);
    } else if (i == 1) {
        printf("%d, ", num);
    } else {
        int nxtNo = prNo + num;
        printf("%d, ", nxtNo);
        prNo = num;
        num = nxtNo;
    }

    i++;
    fibonacci_sq(term);
}

void elements_recursion(int *arr, int n, int len) {
    if (n > len) {
        printf("Error: n is greater than the length of the array\n");
        return;
    }
    if (n <= 0) {
        return;
    } else {
        printf("%d, ", *arr);       // Print the current element
        elements_recursion(arr+1, n-1, len); // Increment the pointer and decrease n
    }
}

int count_digits(int n){
    if (n == 0) {
        return 0;
    } else {
        return 1 + count_digits(n/10);
    }
}

int sum_digits(int n){
    if (n == 0){
        return 0;
    } else {
        return n % 10 + sum_digits(n/10);
    }
}

int gcd(int i, int j){
    while (i != j){
        if (i > j){
            return gcd(i-j, j);
        } else{
            return gcd(i, j-i);
        }
    }
    return i;
}

int largest_element(int *arr, int length){
    if (length == 1) {
        return *arr;
    }

    int max_of_rest = largest_element(arr + 1, length - 1);
    if (*arr > max_of_rest) {
        return *arr;
    } else {
        return max_of_rest;
    }
}

void reverse(char *str) {
    if (*str) {
        reverse(str + 1);
        printf("%c", *str);
    }
}

int factorial(int n){
    if (n == 1){
        return 1;
    } else {
        return n * factorial(n-1);
    }
}

void decimaltobinary(int n){
    if (n == 0){
        return;
    } else {
        decimaltobinary(n/2);
        printf("%d", n%2);
    }
}
int i;

int prime(int n) {
    if(i==1)
    {
        return 1;
    }
    else if(n %i==0)
    {
        return 0;
    }
    else
    {
        i = i -1;
        prime(n);
    }
}

int lcm(int n1, int n2) {
    return (n1 * n2) / gcd(n1, n2);
}

void even_or_odd(int type, int n) {
    if (n <= 0) {
        return;
    }

    // If current number is of the same type we're looking for
    if (type == 0 && n % 2 == 0) {
        even_or_odd(type, n-1);
        printf("%d  ", n);
    } else if (type == 1 && n % 2 == 1) {
        even_or_odd(type, n-1);
        printf("%d  ", n);
    } else {
        // If current number is not of the type we're looking for, just skip it
        even_or_odd(type, n-1);
    }
}

#define MAX 10

int first[MAX][MAX] = {{1}, {2}};
int second[MAX][MAX] = {{3, 4}};
int result[MAX][MAX];

int multiplyMatricesRecursively(int row, int col, int innerDim, int sum) {
    if(innerDim == 0) {
        return sum + first[row][innerDim] * second[innerDim][col];
    }
    return multiplyMatricesRecursively(row, col, innerDim-1, sum + first[row][innerDim] * second[innerDim][col]);
}

void calculateResult(int row, int col, int rows, int columns) {
    if(row == rows) {
        return;
    }
    if(col == columns) {
        calculateResult(row+1, 0, rows, columns);
    } else {
        result[row][col] = multiplyMatricesRecursively(row, col, columns-1, 0);
        calculateResult(row, col+1, rows, columns);
    }
}

void isPalindrome(char *start, char *end) {
    if (start >= end) {
        printf("Palindrome\n");
        return;
    }

    if (*start == *end) {
        return isPalindrome(start + 1, end - 1);
    }

    printf("Not a palindrome\n");
}

int powerOf(int base, int exponent){
    if (exponent == 0){
        return 1;
    } else {
        return base * powerOf(base, exponent-1);
    }
}

// hailStone sequence: if n is even, divide by 2. if n is odd, multiply by 3 and add 1
void hailStone(int n) {
    if (n == 1) {
        printf("%d ", n);
        return;
    }

    printf("%d ", n);

    if (n % 2 == 0) {
        hailStone(n / 2);
    } else {
        hailStone((n * 3) + 1);
    }
}

void copyStrings(char *str1, char *str2){
    if (*str1 == '\0') {
        *str2 = '\0';
        return;
    }
    *str2 = *str1;
    copyStrings(str1 + 1, str2 + 1);
}

bool isUpper(char c) {
    return c >= 'A' && c <= 'Z';
}

void capitalLetter(char *arr) {
    if (*arr == '\0') {
        printf("No capitals.\n");
        return;
    }
    if (isUpper(*arr)) {
        printf("The first capital letter is: %c\n", *arr);
        return;
    } else {
        capitalLetter(arr + 1);
    }
}

void binarySearch(int n, int arr[], int *start, int *end) {
    if (*start <= *end) {
        int mid = (*start + *end) / 2;

        if (arr[mid] == n) {
            printf("Found in array\n");
            return;
        }

        if (arr[mid] < n) {
            int newStart = mid + 1;
            binarySearch(n, arr, &newStart, end);
            return;
        }
        else {
            int newEnd = mid - 1;
            binarySearch(n, arr, start, &newEnd);
            return;
        }
    }
    printf("Not found\n");
}

int main(void) {
    //// sum of numbers
//    printf("Sum: %d\n", sum_numbers(5));
    //// fibonacci sequence
//    printf("Fibonacci: ");
//    fibonacci_sq(10);
//    printf("\n");
    //// elements of array
//    int arr[] = {1,2,3,4,5};
//    int len = sizeof(arr) / sizeof(arr[0]);
//    elements_recursion(arr, 5, len);
    //// count digits
//    printf("Digits: %d\n", count_digits(12345));
    //// sum of digits
//    printf("Sum of Digits: %d\n", sum_digits(25));
    //// gcd
//    printf("GCD: %d\n", gcd(10, 50));
    //// largest element
//    int arr[] = {55, 30, 15, 20, 25};
//    int len = sizeof(arr)/sizeof(arr[0]);
//    printf("Largest element: %d\n", largest_element(arr, len));
    //// reverse string
//    char str[] = "Hello World";
//    reverse(str);
    //// factorial
//    printf("Factorial: %d\n", factorial(5));
    //// decimal to binary
//    decimaltobinary(13);
    //// prime number
//    int n1 = 13, primeNo;
//    int i = n1/2;
//    primeNo = prime(n1);
//    if(primeNo==1)
//        printf(" The number %d is a prime number. \n\n",n1);
//    else
//        printf(" The number %d is not a prime number. \n\n",n1);
    //// lowest common denominator
//    printf("LCD: %d\n", lcm(4, 6));
    //// even and odd
//    even_or_odd(1, 10);
    //// matrix multiplication
//    int rowsFirst = 2, colsFirst = 1, rowsSecond = 1, colsSecond = 2, i , j;
//    calculateResult(0, 0, rowsFirst, colsSecond);
//
//    printf("\nThe multiplication of two matrices is :\n");
//    for(i = 0; i < rowsFirst; i++) {
//        for(j = 0; j < colsSecond; j++) {
//            printf("%d\t", result[i][j]);
//        }
//        printf("\n");
//    }
    //// palindrome
//    char str[] = "racecar";
//    int length = sizeof(str) - 1;
//    printf("Length: %d\n", length);
//    isPalindrome(str, str+length-1);
    //// power of
//    printf("Power of: %d\n", powerOf(2, 3));
    //// hailStone
//    hailStone(13);
    //// copy strings
//    char str1[] = "hello";
//    char str2[50];
//    copyStrings(str1, str2);
//    printf("Copied String: %s", str2);
    //// binarySearch
//    int arr[] = {1, 2, 5, 6, 9};
//    int start = 0;
//    int end = (sizeof(arr)/sizeof(arr[0])) - 1;
//    binarySearch(6, arr, &start, &end);
    //// capital letter
//    char str[] = "theMonkey";
//    capitalLetter(str);
    return 0;
}