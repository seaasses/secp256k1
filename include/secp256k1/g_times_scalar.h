#ifndef G_TIMES_SCALAR
#define G_TIMES_SCALAR

#include "structs/big_uint.h"
#include "structs/point.h"

void g_times_scalar(const Uint256 *scalar, Point *result_point);

#endif