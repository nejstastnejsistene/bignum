#include "bignum.h"

inline void mul(digit_t x, digit_t y, digit_t *hi, digit_t *lo) {
    uint64_t xy = (uint64_t)x * (uint64_t)y; 
    *hi = xy >> 32;
    *lo = xy;
}

