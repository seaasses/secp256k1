#ifndef UINT256_ADDITION_WITH_OVERFLOW_FLAG
#define UINT256_ADDITION_WITH_OVERFLOW_FLAG

#include "structs/uint256.h"

void uint256_addition_with_overflow_flag(const Uint256 *a, const Uint256 *b,
                                         Uint256 *result, unsigned int *overflowFlag);

#endif