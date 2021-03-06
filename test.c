#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bignum.h"

/* Convert a string to bignum, and back to a string. */
void test_stringify(char *s, int base) {
    bignum *x = from_string(s, base);
    printf("0b%s\n", to_string(x, base));
}

void test_add(bignum *x, bignum *y) {
    printf("0b%s\n", to_string(add(x, y), 2));
}

void test_add_op(digit_t x, digit_t y) {
    digit_t hi, lo;
    _add(x, y, &hi, &lo);
    printf("0x%x << 32 | 0x%x\n", hi, lo);
}

/* Multiply two numbers and print the hi and lo resulting words as an
 * expression to be evalated in Python.
 */
void test_mul_op(digit_t x, digit_t y) {
    digit_t hi, lo;
    _mul(x, y, &hi, &lo);
    printf("0x%x << 32 | 0x%x\n", hi, lo);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: ./test <name> <args...>\n");
        exit(2);
    }
    if (strcmp(argv[1], "stringify") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Usage: ./test stringify <string> <base>\n");
            exit(2);
        }
        test_stringify(argv[2], atoi(argv[3]));
    } else if (strcmp(argv[1], "add") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Usage: ./test add <x> <y>\n");
            exit(2);
        }
        test_add(from_string(argv[2], 2), from_string(argv[3], 2)); 
    } else if (strcmp(argv[1], "add_op") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Usage: ./test add_op <x> <y>\n");
            exit(2);
        }
        test_add_op(atoi(argv[2]), atoi(argv[3])); 
    } else if (strcmp(argv[1], "mul_op") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Usage: ./test mul_op <x> <y>\n");
            exit(2);
        }
        test_mul_op(atoi(argv[2]), atoi(argv[3])); 
    } else {
        fprintf(stderr, "Unrecognized command\n");
        exit(2);
    }
    return 0;
}
