#ifndef UINT256_MULTIPLICATION
#define UINT256_MULTIPLICATION

#include "structs/uint256.h"
#include "structs/uint512.h"

void uint256_multiplication(const Uint256 *a, const Uint256 *b, Uint512 *result);

#endif