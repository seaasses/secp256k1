#ifndef BIG_UINT_SUBTRACTION
#define BIG_UINT_SUBTRACTION

#include "structs/big_uint.h"

void uint256_subtraction_with_underflow_flag(const Uint256 *a, const Uint256 *b, Uint256 *result, unsigned int *underflowFlag);
void uint256_subtraction(const Uint256 *a, const Uint256 *b, Uint256 *result);

#endif