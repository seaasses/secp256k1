#ifndef JACOBIAN_POINT_AFFINE_POINT_ADDITION
#define JACOBIAN_POINT_AFFINE_POINT_ADDITION

#include "structs/point.h"

void jacobian_point_affine_point_addition(const JacobianPoint *point_a_mont, const Point *point_b_mont, JacobianPoint *result_point);

#endif