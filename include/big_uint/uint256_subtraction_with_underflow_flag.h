#ifndef UINT256_SUBTRACTION_WITH_UNDERFLOW_FLAG
#define UINT256_SUBTRACTION_WITH_UNDERFLOW_FLAG

#include "structs/uint256.h"

void uint256_subtraction_with_underflow_flag(const Uint256 *a, const Uint256 *b,
                                         Uint256 *result, unsigned int *underflowFlag);

#endif