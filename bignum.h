#ifndef BIGNUM_H
#define BIGNUM_H

#define MAX(a,b) (((a)<(b))?(a):(b))

#include <stdint.h>

/* Multiplying 64 bit numbers can overflow, and it doesn't seem
 * possible to access the HI/LO registers outside of assembly, so
 * I'm instead reducing the bignum digit size to avoid the overflow.
 */
#define digit_t uint32_t

typedef struct {
    int num_digits;
    digit_t *digits; // Big endian.
} bignum;

bignum *from_string(char *s, int base);
char *to_string(bignum *x, int base);
bignum *bignum_add(bignum *x, bignum *y);
inline void add(digit_t x, digit_t y, digit_t *hi, digit_t *lo);
inline void add3(digit_t x, digit_t y, digit_t z, digit_t *hi, digit_t *lo);
inline void mul(digit_t x, digit_t y, digit_t *hi, digit_t *lo);

#endif
