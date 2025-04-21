#include "constants/secp256k1.h"
#include "modular_operations/modular_addition.h"
#include "modular_operations/modular_double.h"
#include "modular_operations/modular_subtraction.h"
#include "montgomery/montgomery_multiplication.h"
#include "secp256k1/jacobian_point_addition_jacobian_montgomery_plus_affine_montgomery.h"

inline void jacobian_point_addition_jacobian_montgomery_plus_affine_montgomery(const JacobianPoint *a, const Point *b, JacobianPoint *result_point)
{

    Uint256 tmp_0, tmp_1, tmp_2;

    montgomery_multiplication(&a->z, &a->z, &tmp_2);
    montgomery_multiplication(&tmp_2, &a->z, &result_point->y);
    montgomery_multiplication(&b->x, &tmp_2, &result_point->z);
    montgomery_multiplication(&b->y, &result_point->y, &tmp_2);
    modular_subtraction(&result_point->z, &a->x, &result_point->z);
    modular_subtraction(&tmp_2, &a->y, &tmp_2);
    montgomery_multiplication(&result_point->z, &result_point->z, &result_point->y);
    montgomery_multiplication(&a->x, &result_point->y, &tmp_0);
    montgomery_multiplication(&result_point->y, &result_point->z, &result_point->y);
    modular_double(&tmp_0, &tmp_1);
    montgomery_multiplication(&tmp_2, &tmp_2, &result_point->x);
    modular_subtraction(&result_point->x, &result_point->y, &result_point->x);
    modular_subtraction(&result_point->x, &tmp_1, &result_point->x); // result_point.x = X3 :D

    montgomery_multiplication(&a->y, &result_point->y, &tmp_1);
    modular_subtraction(&tmp_0, &result_point->x, &result_point->y);
    montgomery_multiplication(&result_point->y, &tmp_2, &result_point->y);
    modular_subtraction(&result_point->y, &tmp_1, &result_point->y); // result_point.y = Y3 :D

    montgomery_multiplication(&result_point->z, &a->z, &result_point->z); // result_point.z = Z3 :D

}
