#ifndef MONTGOMERY_MULTIPLICATION
#define MONTGOMERY_MULTIPLICATION

#include "structs/big_uint.h"

void montgomery_multiplication(const Uint256 *a, const Uint256 *b, Uint256 *result);

#endif