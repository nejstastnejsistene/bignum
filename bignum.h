#ifndef BIGNUM_H
#define BIGNUM_H

#include <stdint.h>

/* Multiplying 64 bit numbers can overflow, and it doesn't seem
 * possible to access the HI/LO registers outside of assembly, so
 * I'm instead reducing the bignum digit size to avoid the overflow.
 */
#define digit_t uint32_t

/* Multiply two 32 bits and return the hi and lo result words. */
inline void mul(digit_t x, digit_t y, digit_t *hi, digit_t *lo);

#endif
