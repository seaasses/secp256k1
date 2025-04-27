#ifndef MONTGOMERY_REDUCTION
#define MONTGOMERY_REDUCTION

#include "structs/big_uint.h"
#include "structs/big_uint.h"

void montgomery_reduction(const Uint512 *x, Uint256 *x_result);

#endif