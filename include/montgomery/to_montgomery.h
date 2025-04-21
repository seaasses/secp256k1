#ifndef TO_MONTGOMERY
#define TO_MONTGOMERY

#include "structs/uint256.h"

void to_montgomery(const Uint256 *x, Uint256 *x_montgomery);

#endif