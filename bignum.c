#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bignum.h"

bignum *from_string(char *s, int base) {
    if (base == 2) {
        int len, msd, extrabit, i, j;
        bignum *val;
        len = strlen(s);
        msd = len % 32; // The digits at the front that go with the msb.
        extrabit = msd > 0; // Whether to handle a special case first digit.

        // Allocate bignum.
        val = malloc(sizeof(bignum));
        if (!val) {
            perror("Error allocating bignum");
            exit(1);
        }
        val->num_digits = len / 32 + extrabit; 
        val->digits = malloc(sizeof(digit_t) * val->num_digits);
        if (!val->digits) {
            perror("Error allocating bignum");
            exit(1);
        }

        // Set the most significant digit from the leading bits.
        for (i = 0; i < msd; i++) {
            val->digits[0] |= (s[i] - '0') << (msd - i - 1);
        }
        // Set the remaining digits.
        for (i = 0; i < len - msd; i++) {
            j = extrabit + i / 32;
            val->digits[j] |= (s[msd + i] - '0') << (31 - i % 32);
        }
        return val;
    } else {
        return NULL;
    }    
}

char *to_string(bignum *x, int base) {
    if (base == 2) {
        int i, j, bit;
        char *buf, *p;
        // Special case for most significant digit.
        buf = NULL;
        for (j = 0; j < 32; j++) {
            bit = (x->digits[0] >> (31 - j)) & 1;
            // Skip leading zeroes.
            if (bit && !buf) {
                p = buf = malloc(x->num_digits * 32 - j);
            }
            if (buf) {
                // Assign the bits.
                *p++ = bit + '0';
            }
        }
        // Handle the remaining digits.
        for (i = 1; i < x->num_digits; i++) {
            for (j = 31; j >= 0; j--) {
                bit = (x->digits[i] >> j) & 1;
                *p++ = bit + '0';
            }
        }
        // Null terminator.
        *p = 0;
        return buf;
   } else {
        return NULL;
   } 
}

/* Multiply two 32 bits and return the hi and lo result words. */
inline void mul(digit_t x, digit_t y, digit_t *hi, digit_t *lo) {
    uint64_t xy = (uint64_t)x * (uint64_t)y; 
    *hi = xy >> 32;
    *lo = xy;
}
