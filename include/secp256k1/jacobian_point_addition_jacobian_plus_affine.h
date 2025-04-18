#ifndef JACOBIAN_POINT_ADDITION_JACOBIAN_PLUS_AFFINE
#define JACOBIAN_POINT_ADDITION_JACOBIAN_PLUS_AFFINE

#include "structs/point.h"

void jacobian_point_addition_jacobian_plus_affine(const JacobianPoint *point_a, const Point *point_b, JacobianPoint *result_point);

#endif