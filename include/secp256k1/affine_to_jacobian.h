#ifndef AFFINE_TO_JACOBIAN
#define AFFINE_TO_JACOBIAN

#include "structs/point.h"

void affine_to_jacobian(const Point *point, JacobianPoint *result_point);

#endif