#ifndef FROM_MONTGOMERY
#define FROM_MONTGOMERY

#include "structs/big_uint.h"

void from_montgomery(const Uint256 *x_montgomery, Uint256 *x);

#endif