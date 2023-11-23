#include <stdio.h>
#include <stdlib.h>

long long int logicaladder(long long int num1, long long int num2) {
    long long int carry;
    while (num2 != 0) {
        carry = num1 & num2;
        num1 = num1 ^ num2;
        num2 = carry << 1;
    }
    return num1;
}

long long int detectoverflow(long long int sum, int bitwidth, int shift) {
    long long extended_sum = (long long)sum;
    long long max = (1LL << bitwidth) - 1;
    long long min = -(1LL << bitwidth);

    if (extended_sum > max || extended_sum < min) {
        sum = sum >> shift;
        printf("Result after right shift: %lld\n", sum);
        printf("Overflow detected within the specified bitwidth.\n");
    } else {
        printf("Result of addition: %lld\n", sum);
    }
    return sum;
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: <bitwidth> <num1> <num2> <shift number>\n");
        return -1;
    }

    int bitwidth = atoi(argv[1]);
    long long int num1 = atoll(argv[2]);
    long long int num2 = atoll(argv[3]);
    int shift = atoi(argv[4]);
    long long int sum = logicaladder(num1, num2);
    detectoverflow(sum, bitwidth - 1, shift);
    return 0;
}
