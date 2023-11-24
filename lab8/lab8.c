#include <stdio.h>
#include <stdlib.h>

long long logicaladder(long long a, long long b) {
    while (b != 0) {
        long long carry = a & b;
        a = a ^ b;
        b = carry << 1;
    }
    return a;
}

long long detectoverflow(long long a, long long b, int bitwidth, int shift) {
    long long result = logicaladder(a, b);

    long long overflow_mask = (result ^ a) & (result ^ b) & (1LL << (bitwidth - 1));

    if (overflow_mask) {
        long long shifted_result = result >> shift;
        printf("Result after right shift by %d: %lld\n", shift, shifted_result);
        printf("Overflow detected within the specified bitwidth.\n");
        return shifted_result;
    } else {
        printf("Result of addition: %lld\n", result);
        return result;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Invalid number of arguments.\n");
        return 1;
    }

    int bitwidth = atoi(argv[1]);
    long long a = atoll(argv[2]);
    long long b = atoll(argv[3]);
    int shift = atoi(argv[4]);

    if (bitwidth != 8 && bitwidth != 16 && bitwidth != 32 && bitwidth != 64) {
        printf("Invalid bitwidth. Supported values are 8, 16, 32, 64.\n");
        return 1;
    }

    long long max_value = (1LL << (bitwidth - 1)) - 1;
    long long min_value = -(1LL << (bitwidth - 1));

    if (a > max_value || a < min_value || b > max_value || b < min_value) {
        printf("Invalid value. Supported values are %lld to %lld.\n", min_value, max_value);
        return 1;
    }

    if (shift < 0 || shift > bitwidth) {
        printf("Invalid shift value. Supported values are 0 to %d.\n", bitwidth);
        return 1;
    }

    detectoverflow(a, b, bitwidth, shift);

    return 0;
}
