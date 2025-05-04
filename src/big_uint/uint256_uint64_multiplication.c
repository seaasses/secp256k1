#include "big_uint/uint256_uint64_multiplication.h"
#include "big_uint/uint64_multiplication.h"
#include "big_uint/big_uint_multiplication_helper.h"

#include <stdio.h>

void uint256_uint64_multiplication(Uint256 *a, unsigned long long b, Uint320 *result)
{
    unsigned long long carry_high = 0;
    unsigned long long carry_low;

    uint64_multiplication(a->limbs[3], b, carry_low, result->limbs[4]); // first limb set (OK)

    result->limbs[3] = carry_low;
    carry_low = carry_high;
    carry_high = 0;
    add_component_to_limb(a->limbs[2], b, carry_high, carry_low, result->limbs[3]);

    result->limbs[2] = carry_low;
    carry_low = carry_high;
    carry_high = 0;
    add_component_to_limb(a->limbs[1], b, carry_high, carry_low, result->limbs[2]);

    result->limbs[1] = carry_low;
    carry_low = carry_high;
    carry_high = 0;
    add_component_to_limb(a->limbs[0], b, carry_high, carry_low, result->limbs[1]);

    result->limbs[0] = carry_low;
}