#include "montgomery/montgomery_multiplication.h"
#include "uint256/multiplication.h"
#include "montgomery/montgomery_reduction.h"

inline void montgomery_multiplication(const Uint256 *a_m, const Uint256 *b_m, Uint256 *result_m)
{
    // inplace safe

    Uint512 t;

    uint256_multiplication(a_m, b_m, &t); 
    montgomery_reduction(&t, result_m);
}