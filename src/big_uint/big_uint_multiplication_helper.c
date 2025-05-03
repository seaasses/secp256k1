#include "big_uint/big_uint_multiplication_helper.h"
#include "big_uint/uint64_multiplication.h"

#include "structs/big_uint.h"

// TODO: stop using this. I think I can do the multiplications better
inline void uint64_multiplication_result_high_and_low(const unsigned long long a, const unsigned long long b, unsigned long long *high, unsigned long long *low)
{
    Uint128 result_tmp;
    uint64_multiplication(a, b, &result_tmp);

    *high = result_tmp.limbs[0];
    *low = result_tmp.limbs[1];
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

    uint64_multiplication_result_high_and_low(a_limb, b_limb, &carry_tmp_low, &result_tmp);

    uint64_sum_with_overflow_flag(*carry_low, carry_tmp_low, carry_low, &carry_tmp_high);
    *carry_high += carry_tmp_high;
    uint64_sum_with_overflow_flag(*result_limb, result_tmp, result_limb, &carry_tmp_low);
    uint64_sum_with_overflow_flag(*carry_low, carry_tmp_low, carry_low, &carry_tmp_high);
    *carry_high += carry_tmp_high;
}