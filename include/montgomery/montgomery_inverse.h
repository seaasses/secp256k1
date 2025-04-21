#ifndef MONTGOMERY_INVERSE
#define MONTGOMERY_INVERSE

#include "structs/uint256.h"

void montgomery_inverse(const Uint256 *a_mont, Uint256 *a_inv_mont);

#endif