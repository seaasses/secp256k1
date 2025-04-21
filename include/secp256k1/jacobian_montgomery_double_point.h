#ifndef JACOBIAN_MONTGOMERY_DOUBLE_POINT
#define JACOBIAN_MONTGOMERY_DOUBLE_POINT

#include "structs/point.h"

void jacobian_montgomery_double_point(const JacobianPoint *point_mont, JacobianPoint *result_point_mont);

#endif