#include "modular_operations/modular_multiplication.h"
#include "constants/secp256k1.h"
#include "modular_operations/modular_double.h"
#include "modular_operations/modular_addition.h"

inline void modular_multiplication(const Uint256 *a, const Uint256 *b, Uint256 *result)
{ // inplace semi-safe. safe if result = a

    // I know that a and b are already < P, no need to modules before starting
    Uint256 local_a = *a;
    Uint256 to_add;
    unsigned long long limb;
    unsigned long long to_add_mask;
    *result = (Uint256){
        .limbs = {0, 0, 0, 0}};

    #pragma unroll
    for (unsigned char limb_index = 3; limb_index != 0xFF; --limb_index)
    {
        limb = b->limbs[limb_index];
        #pragma unroll
        for (unsigned int i = 0; i != 64; i++)
        {

            to_add_mask = -(limb & 1);

            to_add = (Uint256){
                .limbs = {
                    local_a.limbs[0] & to_add_mask,
                    local_a.limbs[1] & to_add_mask,
                    local_a.limbs[2] & to_add_mask,
                    local_a.limbs[3] & to_add_mask,
                }};

            modular_addition(result, &to_add, result);
            modular_double(&local_a, &local_a);

            limb >>= 1;
        }
    }
}
