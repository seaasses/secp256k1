#ifndef BIG_UINT_MULTIPLICATION
#define BIG_UINT_MULTIPLICATION

#include "structs/big_uint.h"

void uint256_multiplication(const Uint256 *a, const Uint256 *b, Uint512 *result);
void uint256_uint64_multiplication(Uint256 *a, unsigned long long b, Uint320 *result);

#endif