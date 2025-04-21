#include "montgomery/from_montgomery.h"
#include "constants/montgomery.h"
#include "montgomery/montgomery_reduction.h"
#include "structs/uint512.h"

inline void from_montgomery(Uint256 *x_montgomery, Uint256 *x)
{
    // inplace safe

    // x_montgomery = x * R mod N
    // basically returns x_montgomery * R^(-1) mod N = x mod N
    // by using the montgomery reduction, that returns a * R^(-1) mod N

    Uint512 tmp = {.limbs = {
                       0,
                       0,
                       0,
                       0,
                       x_montgomery->limbs[0],
                       x_montgomery->limbs[1],
                       x_montgomery->limbs[2],
                       x_montgomery->limbs[3],

                   }};

    montgomery_reduction(&tmp, x);
}