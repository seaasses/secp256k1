#ifndef JACOBIAN_TO_AFFINE
#define JACOBIAN_TO_AFFINE

#include "structs/point.h"

void jacobian_to_affine(const JacobianPoint *point_jac, Point *point);

#endif