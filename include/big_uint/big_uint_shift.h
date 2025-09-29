#ifndef BIG_UINT_SHIFT
#define BIG_UINT_SHIFT

#include "structs/big_uint.h"

void uint256_shift_left(const Uint256 *x, Uint256 *result);
void uint256_shift_right(const Uint256 *x, Uint256 *result);

#endif