#ifndef JACOBIAN_MONTGOMERY_TO_AFFINE
#define JACOBIAN_MONTGOMERY_TO_AFFINE

#include "structs/point.h"

void jacobian_montgomery_to_affine(const JacobianPoint *point_jac_mont, Point *point);

#endif