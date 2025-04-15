#include "uint256/shift_right.h"

#pragma inline
void uint256_shift_right(const Uint256 *x, Uint256 *result)
{
  // inplace safe
  result->limbs[3] = (x->limbs[3] >> 1) | (x->limbs[2] << 63);
  result->limbs[2] = (x->limbs[2] >> 1) | (x->limbs[1] << 63);
  result->limbs[1] = (x->limbs[1] >> 1) | (x->limbs[0] << 63);
  result->limbs[0] = x->limbs[0] >> 1;
}