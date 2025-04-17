#include "modular_operations/modular_exponentiation.h"
#include "constants/secp256k1.h"
#include "modular_operations/modular_multiplication.h"

inline void modular_exponentiation(const Uint256 *base, const Uint256 *exponent, Uint256 *result)
{
    // inplace semi safe. Safe when result = base

    // base will be < modulus, so no need to modulus before starting
    Uint256 localBase = *base;
    Uint256 tmp;
    Uint256 toMultiply;

    unsigned long long limb;
    unsigned long long toMultiplyMask;

    *result = (Uint256){.limbs = {0, 0, 0, 1}};

#pragma unroll
    for (int i = 3; i >= 0; --i)
    {
        limb = exponent->limbs[i];
#pragma unroll
        for (unsigned int i = 0; i < 32; ++i)
        {
            toMultiplyMask = -(limb & 1);
            toMultiply = (Uint256){
                .limbs = {
                    localBase.limbs[0] & toMultiplyMask,
                    localBase.limbs[1] & toMultiplyMask,
                    localBase.limbs[2] & toMultiplyMask,
                    (localBase.limbs[3] & toMultiplyMask) | ((~toMultiplyMask) & 1)}};

            modular_multiplication(result, &toMultiply, result);

            modular_multiplication(&localBase, &localBase, &tmp); // base = base^2
            // localBase is in tmp now, instead of *localBase = tmp, I will use tmp as localBase
            // inside this iteration and loop half as long

            limb >>= 1;
            toMultiplyMask = -(limb & 1);

            toMultiply = (Uint256){
                .limbs = {
                    tmp.limbs[0] & toMultiplyMask,
                    tmp.limbs[1] & toMultiplyMask,
                    tmp.limbs[2] & toMultiplyMask,
                    (tmp.limbs[3] & toMultiplyMask) | ((~toMultiplyMask) & 1)}};

            modular_multiplication(result, &toMultiply, result);

            modular_multiplication(&tmp, &tmp, &localBase); // base = base^2
            // localBase is again in localBase
            limb >>= 1;
        }
    }
}
