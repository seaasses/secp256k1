#ifndef JACOBIAN_TO_AFFINE
#define JACOBIAN_TO_AFFINE

#include "structs/point.h"

void jacobian_to_affine(const JacobianPoint *point, Point *result_point);

#endif