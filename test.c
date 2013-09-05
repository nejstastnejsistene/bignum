#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bignum.h"

/* Multiply two numbers and print the hi and lo resulting words as an
 * expression to be evalated in Python.
 */
void test_mul(digit_t x, digit_t y) {
    digit_t hi, lo;
    mul(x, y, &hi, &lo);
    printf("0x%x << 32 | 0x%x\n", hi, lo);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: ./test <name> <args...>\n");
        exit(2);
    }
    if (strcmp(argv[1], "mul") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Usage: ./test mul x y\n");
            exit(2);
        }
        test_mul(atoi(argv[2]), atoi(argv[3])); 
    } else {
        fprintf(stderr, "Unrecognized command\n");
        exit(2);
    }
    return 0;
}
