#include "modular_operations/modular_subtraction.h"
#include "constants/secp256k1.h"
#include "big_uint/uint256_subtraction_with_underflow_flag.h"
#include "big_uint/uint256_addition.h"

inline void modular_subtraction(const Uint256 *a, const Uint256 *b, Uint256 *result)
{

    unsigned int underflow_flag;
    Uint256 tmp;

    uint256_subtraction_with_underflow_flag(a, b, &tmp, &underflow_flag);

    unsigned long long mask_to_sum = -((unsigned long long)underflow_flag);
    const Uint256 toSum = {.limbs = {
                               SECP256K1_P_0 & mask_to_sum,
                               SECP256K1_P_1 & mask_to_sum,
                               SECP256K1_P_2 & mask_to_sum,
                               SECP256K1_P_3 & mask_to_sum,
                           }};

    uint256_addition(&tmp, &toSum, result);
}
