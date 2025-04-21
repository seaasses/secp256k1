#include "secp256k1/jacobian_to_affine.h"
#include "structs/uint256.h"
#include "modular_operations/modular_exponentiation.h"
#include "modular_operations/modular_multiplication.h"
#include "constants/secp256k1.h"

inline void jacobian_to_affine(const JacobianPoint *point, Point *result_point)
{
    result_point->x = (Uint256)SECP256K1_P_MINUS_2;
    modular_exponentiation(&point->z, &result_point->x, &result_point->y);        // result_point.x = p-2, result.y = z^(-1),
    modular_multiplication(&result_point->y, &result_point->y, &result_point->x); // result_point.x = z^(-2), result_point.y = z^(-1)
    modular_multiplication(&result_point->y, &result_point->x, &result_point->y); // result_point.x = z^(-2), result_point.y = z^(-3)

    modular_multiplication(&result_point->x, &point->x, &result_point->x); // result_point.x = z^(-2) * x
    modular_multiplication(&result_point->y, &point->y, &result_point->y); // result_point.y = z^(-3) * y
}