#include "big_uint/uint256_multiplication.h"

inline void uint64_multiplication(const unsigned long long a, const unsigned long long b, unsigned long long *high, unsigned long long *low)
{
    __uint128_t result = (__uint128_t)a * (__uint128_t)b;

    *low = (unsigned long long)result;
    *high = (unsigned long long)(result >> 64);
}

inline void uint64_sum_with_overflow_flag(const unsigned long long a, const unsigned long long b, unsigned long long *result, unsigned long long *overflow_flag)
{
    *result = a + b;
    *overflow_flag = *result < a;
}

inline void add_component_to_limb(unsigned long long a_limb, unsigned long long b_limb,
                                  unsigned long long *carry_high, unsigned long long *carry_low, unsigned long long *result_limb)
{
    unsigned long long carry_tmp_low, carry_tmp_high, result_tmp;

    uint64_multiplication(a_limb, b_limb, &carry_tmp_low, &result_tmp);

    uint64_sum_with_overflow_flag(*carry_low, carry_tmp_low, carry_low, &carry_tmp_high);
    *carry_high += carry_tmp_high;
    uint64_sum_with_overflow_flag(*result_limb, result_tmp, result_limb, &carry_tmp_low);
    uint64_sum_with_overflow_flag(*carry_low, carry_tmp_low, carry_low, &carry_tmp_high);
    *carry_high += carry_tmp_high;
}

inline void uint256_multiplication(const Uint256 *a, const Uint256 *b, Uint512 *result)
{
    unsigned long long carry_high = 0;
    unsigned long long carry_low;

    // limb 7
    uint64_multiplication(a->limbs[3], b->limbs[3], &carry_low, &result->limbs[7]); // first limb set (OK)

    // limb 6
    ////////////////////////////////////////////////////////////////////////////////


    result->limbs[6] = carry_low; // start with carry low
    carry_low = carry_high;
    carry_high = 0;
    add_component_to_limb(a->limbs[3], b->limbs[2], &carry_high, &carry_low, &result->limbs[6]);
    add_component_to_limb(a->limbs[2], b->limbs[3], &carry_high, &carry_low, &result->limbs[6]);

    // limb 5
    ////////////////////////////////////////////////////////////////////////////////

    result->limbs[5] = carry_low; // start with carry low
    carry_low = carry_high;
    carry_high = 0;
    add_component_to_limb(a->limbs[1], b->limbs[3], &carry_high, &carry_low, &result->limbs[5]);
    add_component_to_limb(a->limbs[2], b->limbs[2], &carry_high, &carry_low, &result->limbs[5]);
    add_component_to_limb(a->limbs[3], b->limbs[1], &carry_high, &carry_low, &result->limbs[5]);

    // limb 4
    result->limbs[4] = carry_low; // start with carry low
    carry_low = carry_high;
    carry_high = 0;
    add_component_to_limb(a->limbs[3], b->limbs[0], &carry_high, &carry_low, &result->limbs[4]);
    add_component_to_limb(a->limbs[0], b->limbs[3], &carry_high, &carry_low, &result->limbs[4]);
    add_component_to_limb(a->limbs[1], b->limbs[2], &carry_high, &carry_low, &result->limbs[4]);
    add_component_to_limb(a->limbs[2], b->limbs[1], &carry_high, &carry_low, &result->limbs[4]);

    // limb 3
    result->limbs[3] = carry_low; // start with carry low
    carry_low = carry_high;
    carry_high = 0;
    add_component_to_limb(a->limbs[2], b->limbs[0], &carry_high, &carry_low, &result->limbs[3]);
    add_component_to_limb(a->limbs[0], b->limbs[2], &carry_high, &carry_low, &result->limbs[3]);
    add_component_to_limb(a->limbs[1], b->limbs[1], &carry_high, &carry_low, &result->limbs[3]);

    // limb 2
    result->limbs[2] = carry_low; // start with carry low
    carry_low = carry_high;
    carry_high = 0;
    add_component_to_limb(a->limbs[0], b->limbs[1], &carry_high, &carry_low, &result->limbs[2]);
    add_component_to_limb(a->limbs[1], b->limbs[0], &carry_high, &carry_low, &result->limbs[2]);

    // limb 1
    result->limbs[1] = carry_low; // start with carry low
    carry_low = carry_high;
    carry_high = 0;
    add_component_to_limb(a->limbs[0], b->limbs[0], &carry_high, &carry_low, &result->limbs[1]);

    // most significant limb
    result->limbs[0] = carry_low;
}
