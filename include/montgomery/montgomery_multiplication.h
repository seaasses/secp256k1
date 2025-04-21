#ifndef MONTGOMERY_MULTIPLICATION
#define MONTGOMERY_MULTIPLICATION

#include "structs/uint256.h"

void montgomery_multiplication(Uint256 *a, Uint256 *b, Uint256 *result);

#endif