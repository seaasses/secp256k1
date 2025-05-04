#include "big_uint/uint320_uint256_addition.h"

void uint320_uint256_addition(const Uint320 *a, const Uint256 *b, Uint320 *result)
{

    result->limbs[4] = a->limbs[4] + b->limbs[3];
    unsigned int carry = result->limbs[4] < a->limbs[4];

    result->limbs[3] = a->limbs[3] + b->limbs[2] + carry;
    carry = (result->limbs[3] < a->limbs[3]) | ((result->limbs[3] == a->limbs[3]) & carry);

    result->limbs[2] = a->limbs[2] + b->limbs[1] + carry;
    carry = (result->limbs[2] < a->limbs[2]) | ((result->limbs[2] == a->limbs[2]) & carry);

    result->limbs[1] = a->limbs[1] + b->limbs[0] + carry;
    carry = (result->limbs[1] < a->limbs[1]) | ((result->limbs[1] == a->limbs[1]) & carry);

    result->limbs[0] = a->limbs[0] + carry;
}
