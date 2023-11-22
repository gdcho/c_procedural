#include <stdio.h>
#include <stdlib.h>

unsigned long long logicaladder(unsigned long long x, unsigned long long y) {
    while (y != 0) {
        unsigned long long carryOver = x & y;
        x = x ^ y;
        y = carryOver << 1;
    }
    return x;
}

unsigned long long detectAndHandleOverflow(unsigned long long x, unsigned long long y, int width, int rightShift, int* overflowOccurred) {
    unsigned long long maxVal = (1ULL << width) - 1;
    // Check if adding y to x would exceed maxVal
    *overflowOccurred = y > maxVal - x;

    unsigned long long result = logicaladder(x, y);

    if (*overflowOccurred) {
        // If overflow occurs, apply right shift and print message
        printf("Overflow detected within the specified bitwidth.\n");
        return result >> rightShift;
    } else {
        // If no overflow, return the result of addition
        return result;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Error: Incorrect number of arguments.\n");
        fprintf(stderr, "Usage: %s <bitWidth> <value1> <value2> <shift>\n", argv[0]);
        return 1;
    }

    int bitWidth = atoi(argv[1]);
    unsigned long long value1 = strtoull(argv[2], NULL, 10);
    unsigned long long value2 = strtoull(argv[3], NULL, 10);
    int shiftAmount = atoi(argv[4]);

    if (bitWidth != 8 && bitWidth != 16 && bitWidth != 32 && bitWidth != 64) {
        fprintf(stderr, "Error: Unsupported bit width. Choose from 8, 16, 32, or 64.\n");
        return 1;
    }

    int overflowFlag = 0;
    unsigned long long result = detectAndHandleOverflow(value1, value2, bitWidth, shiftAmount, &overflowFlag);

    if (overflowFlag) {
        printf("Result after right shift: %llu\n", result);
        printf("Overflow detected within the specified bitwidth.\n");
    } else {
        printf("Result of addition: %llu\n", result);
    }

    return 0;
}
