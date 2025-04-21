#ifndef MONTGOMERY_REDUCTION
#define MONTGOMERY_REDUCTION

#include "structs/uint256.h"
#include "structs/uint512.h"

void montgomery_reduction(const Uint512 *x, Uint256 *x_result);

#endif