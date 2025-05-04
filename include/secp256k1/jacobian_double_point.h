#ifndef JACOBIAN_DOUBLE_POINT
#define JACOBIAN_DOUBLE_POINT

#include "structs/point.h"

void jacobian_double_point(const JacobianPoint *point_mont, JacobianPoint *result_point_mont);

#endif