#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "bignum.h"

bignum *new_bignum(int num_digits) {
    bignum *x = malloc(sizeof(bignum));
    if (!x) {
        perror("Error allocating bignum");
        exit(1);
    }
    x->num_digits = num_digits;
    x->digits = malloc(sizeof(digit_t) * num_digits);
    if (!x->digits) {
        perror("Error allocating bignum");
        exit(1);
    }
    return x;
}

bignum *from_string(char *s, int base) {
    if (base == 2) {
        int len, msd, extrabit, i, j;
        bignum *val;
        len = strlen(s);
        msd = len % 32; // The digits at the front that go with the msb.
        extrabit = msd > 0; // Whether to handle a special case first digit.

        // Allocate bignum.
        val = new_bignum(len / 32 + extrabit);

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

/* Add two bignums together. */
bignum *add(bignum *x, bignum *y) {
    int num_digits, i;
    digit_t tmp1, tmp2, hi, lo;
    bignum *val;

    num_digits = MAX(x->num_digits, y->num_digits);
    // Check if an additional digit will be required because of overflow.
    if (x->num_digits == y->num_digits &&
            ((uint64_t)x->digits[0] + (uint64_t)y->digits[0]) >> 32) {
        num_digits++;
    }
    val = new_bignum(num_digits);

    hi = 0;
    for (i = 0; i < num_digits; i++) {
        tmp1 = x->num_digits - i > 0 ? x->digits[x->num_digits - i - 1] : 0;
        tmp2 = y->num_digits - i > 0 ? y->digits[y->num_digits - i - 1] : 0;
        lo = 0;
        _add3(hi, tmp1, tmp2, &hi, &lo);
        // Set the current digit.
        val->digits[val->num_digits - i - 1] = lo;
        // The contents of hi are carried to the next digit.
    }
    return val;
}

/* Add two 32 bits and return the hi and lo result words. */
inline void _add(digit_t x, digit_t y, digit_t *hi, digit_t *lo) {
    _add3(x, y, 0, hi, lo);
}

/* Add three 32 bits and return the hi and lo result words. */
inline void _add3(digit_t x, digit_t y, digit_t z, digit_t *hi, digit_t *lo) {
    uint64_t xy = (uint64_t)x + (uint64_t)y + (uint64_t)z; 
    *hi = xy >> 32;
    *lo = xy;
}

/* Multiply two 32 bits and return the hi and lo result words. */
inline void _mul(digit_t x, digit_t y, digit_t *hi, digit_t *lo) {
    uint64_t xy = (uint64_t)x * (uint64_t)y; 
    *hi = xy >> 32;
    *lo = xy;
}
