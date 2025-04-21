#include "montgomery/montgomery_inverse.h"
#include "constants/montgomery.h"
#include "montgomery/montgomery_multiplication.h"
#include "structs/uint256.h"
#include <stdio.h>

void montgomery_inverse(const Uint256 *a_mont, Uint256 *a_inv_mont)
{
    /*
    Given a_mont = a * R mod N
    The result will be:

    a_inv_mont = a_inv * R mod N

    Where:

    a * a_inv mod N = 1  (modular inverse)

    This uses Fermat's Little Theorem to compute the modular inverse.

*/
    // TODO: Since the exponent (N-2) is constant and known at compile time, we can avoid dynamically testing each bit and instead perform the binary exponentiation directly.

    Uint256 exponent = MONTGOMERY_N_MINUS_2;
    Uint256 to_multiply;

    unsigned long long limb;
    unsigned long long to_multiply_mask;

    *a_inv_mont = (Uint256)ONE_IN_MONTGOMERY;

#pragma unroll
    for (unsigned int i = 0; i < 4; ++i)
    {
        limb = exponent.limbs[i];
#pragma unroll
        for (unsigned int j = 0; j < 64; ++j)
        {

            montgomery_multiplication(a_inv_mont, a_inv_mont, a_inv_mont);
            to_multiply_mask = -((limb & 0x8000000000000000) >> 63);
            to_multiply = (Uint256){
                .limbs = {
                    a_mont->limbs[0] & to_multiply_mask,
                    a_mont->limbs[1] & to_multiply_mask,
                    (a_mont->limbs[2] & to_multiply_mask),
                    (a_mont->limbs[3] & to_multiply_mask) | ((~to_multiply_mask) & ONE_IN_MONTGOMERY_3)

                }};

            montgomery_multiplication(a_inv_mont, &to_multiply, a_inv_mont);

            limb <<= 1;
        }
    }
}
