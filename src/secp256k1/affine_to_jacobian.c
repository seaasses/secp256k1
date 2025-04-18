#include "secp256k1/affine_to_jacobian.h"

void affine_to_jacobian(const Point *point, JacobianPoint *result_point)
{
    // (x, z) -> (x, y, 1)
    result_point->x = point->x;
    result_point->y = point->y;
    result_point->z = (Uint256){
        .limbs = {0, 0, 0, 1}}; // z = 1
}