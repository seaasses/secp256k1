#ifndef JACOBIAN_POINT_ADDITION
#define JACOBIAN_POINT_ADDITION

#include "structs/point.h"

void jacobian_point_addition(const JacobianPoint *point_a, const JacobianPoint *point_b, JacobianPoint *result_point);

#endif