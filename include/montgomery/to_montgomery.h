#ifndef TO_MONTGOMERY
#define TO_MONTGOMERY

#include "structs/big_uint.h"

void to_montgomery(const Uint256 *x, Uint256 *x_montgomery);

#endif