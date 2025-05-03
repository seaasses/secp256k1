#include "big_uint/uint64_multiplication.h"

inline void uint64_multiplication(const unsigned long long a, const unsigned long long b, Uint128 *result)
{
    __uint128_t result_128 = (__uint128_t)a * (__uint128_t)b;

    result->limbs[1] = (unsigned long long)result_128;
    result->limbs[0] = (unsigned long long)(result_128 >> 64);
}
