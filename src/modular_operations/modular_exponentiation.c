#include "modular_operations/modular_exponentiation.h"
#include "constants/secp256k1.h"
#include "modular_operations/modular_multiplication.h"

inline void modular_exponentiation(const Uint256 *base, const Uint256 *exponent, Uint256 *result)
{
    // inplace semi safe. Safe when result = base

    // base will be < modulus, so no need to modulus before starting
    Uint256 local_base = *base;
    Uint256 tmp;
    Uint256 to_multiply;

    unsigned long long limb;
    unsigned long long to_multiply_mask;

    *result = (Uint256){.limbs = {0, 0, 0, 1}};

#pragma unroll
    for (int i = 3; i >= 0; --i)
    {
        limb = exponent->limbs[i];
#pragma unroll
        for (unsigned int i = 0; i < 32; ++i)
        {
            to_multiply_mask = -(limb & 1);
            to_multiply = (Uint256){
                .limbs = {
                    local_base.limbs[0] & to_multiply_mask,
                    local_base.limbs[1] & to_multiply_mask,
                    local_base.limbs[2] & to_multiply_mask,
                    (local_base.limbs[3] & to_multiply_mask) | ((~to_multiply_mask) & 1)}};

            modular_multiplication(result, &to_multiply, result);

            modular_multiplication(&local_base, &local_base, &tmp); // base = base^2
            // localBase is in tmp now, instead of *localBase = tmp, I will use tmp as localBase
            // inside this iteration and loop half as long

            limb >>= 1;
            to_multiply_mask = -(limb & 1);

            to_multiply = (Uint256){
                .limbs = {
                    tmp.limbs[0] & to_multiply_mask,
                    tmp.limbs[1] & to_multiply_mask,
                    tmp.limbs[2] & to_multiply_mask,
                    (tmp.limbs[3] & to_multiply_mask) | ((~to_multiply_mask) & 1)}};

            modular_multiplication(result, &to_multiply, result);

            modular_multiplication(&tmp, &tmp, &local_base); // base = base^2
            // localBase is again in localBase
            limb >>= 1;
        }
    }
}
