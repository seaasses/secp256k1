#include "big_uint/uint256_multiplication.h"
#include "big_uint/uint64_multiplication.h"
#include "big_uint/big_uint_multiplication_helper.h"

inline void uint256_multiplication(const Uint256 *a, const Uint256 *b, Uint512 *result)
{
    unsigned long long carry_high = 0;
    unsigned long long carry_low;

    // limb 7
    uint64_multiplication(a->limbs[3], b->limbs[3], carry_low, result->limbs[7]); // first limb set (OK)

    // limb 6
    ////////////////////////////////////////////////////////////////////////////////

    result->limbs[6] = carry_low; // start with carry low
    carry_low = carry_high;
    carry_high = 0;
    add_component_to_limb(a->limbs[3], b->limbs[2], carry_high, carry_low, result->limbs[6]);
    add_component_to_limb(a->limbs[2], b->limbs[3], carry_high, carry_low, result->limbs[6]);

    // limb 5
    ////////////////////////////////////////////////////////////////////////////////

    result->limbs[5] = carry_low; // start with carry low
    carry_low = carry_high;
    carry_high = 0;
    add_component_to_limb(a->limbs[1], b->limbs[3], carry_high, carry_low, result->limbs[5]);
    add_component_to_limb(a->limbs[2], b->limbs[2], carry_high, carry_low, result->limbs[5]);
    add_component_to_limb(a->limbs[3], b->limbs[1], carry_high, carry_low, result->limbs[5]);

    // limb 4
    result->limbs[4] = carry_low; // start with carry low
    carry_low = carry_high;
    carry_high = 0;
    add_component_to_limb(a->limbs[3], b->limbs[0], carry_high, carry_low, result->limbs[4]);
    add_component_to_limb(a->limbs[0], b->limbs[3], carry_high, carry_low, result->limbs[4]);
    add_component_to_limb(a->limbs[1], b->limbs[2], carry_high, carry_low, result->limbs[4]);
    add_component_to_limb(a->limbs[2], b->limbs[1], carry_high, carry_low, result->limbs[4]);

    // limb 3
    result->limbs[3] = carry_low; // start with carry low
    carry_low = carry_high;
    carry_high = 0;
    add_component_to_limb(a->limbs[2], b->limbs[0], carry_high, carry_low, result->limbs[3]);
    add_component_to_limb(a->limbs[0], b->limbs[2], carry_high, carry_low, result->limbs[3]);
    add_component_to_limb(a->limbs[1], b->limbs[1], carry_high, carry_low, result->limbs[3]);

    // limb 2
    result->limbs[2] = carry_low; // start with carry low
    carry_low = carry_high;
    carry_high = 0;
    add_component_to_limb(a->limbs[0], b->limbs[1], carry_high, carry_low, result->limbs[2]);
    add_component_to_limb(a->limbs[1], b->limbs[0], carry_high, carry_low, result->limbs[2]);

    // limb 1
    result->limbs[1] = carry_low; // start with carry low
    carry_low = carry_high;
    carry_high = 0;
    add_component_to_limb(a->limbs[0], b->limbs[0], carry_high, carry_low, result->limbs[1]);

    // most significant limb
    result->limbs[0] = carry_low;
}
