#include "montgomery/to_montgomery.h"
#include "constants/montgomery.h"
#include "montgomery/montgomery_multiplication.h"

inline void to_montgomery(Uint256 *x, Uint256 *x_montgomery)
{
    // inplace safe

    // returns x * R * R * R^(-1) mod N = x * R mod N
    // which is the montgomery form of x

    Uint256 r_squared = MONTGOMERY_R_SQUARED;
    montgomery_multiplication(x, &r_squared, x_montgomery);
}