#include "constants/secp256k1.h"
#include "modular_operations/modular_addition.h"
#include "modular_operations/modular_double.h"
#include "modular_operations/modular_subtraction.h"
#include "modular_operations/modular_multiplication.h"
#include "secp256k1/jacobian_point_addition.h"

inline void jacobian_point_addition(const JacobianPoint *a, const JacobianPoint *b, JacobianPoint *result_point)
{
    // TODO: try to do it with less tmp variables
    Uint256 tmp_0, tmp_1, tmp_2, tmp_3, tmp_4, tmp_5;

    modular_multiplication(&a->z, &a->z, &tmp_4); 
    modular_multiplication(&b->z, &b->z, &tmp_5); 

    modular_multiplication(&a->x, &tmp_5, &result_point->z);
    modular_multiplication(&b->x, &tmp_4, &tmp_0);

    modular_subtraction(&tmp_0, &result_point->z, &tmp_0);

    modular_multiplication(&a->y, &b->z, &tmp_1);
    modular_multiplication(&tmp_1, &tmp_5, &tmp_1);

    modular_multiplication(&b->y, &a->z, &tmp_2);
    modular_multiplication(&tmp_2, &tmp_4, &tmp_2);

    modular_double(&tmp_0, &tmp_3);
    modular_multiplication(&tmp_3, &tmp_3, &result_point->x);

    modular_multiplication(&tmp_0, &result_point->x, &tmp_3);

    modular_multiplication(&result_point->z, &result_point->x, &result_point->z);
    modular_subtraction(&tmp_2, &tmp_1, &tmp_2);
    modular_double(&tmp_2, &tmp_2);

    modular_multiplication(&tmp_2, &tmp_2, &result_point->x);
    modular_double(&result_point->z, &result_point->y);
    modular_subtraction(&result_point->x, &tmp_3, &result_point->x);
    modular_subtraction(&result_point->x, &result_point->y, &result_point->x);

    modular_multiplication(&tmp_1, &tmp_3, &tmp_1);
    modular_double(&tmp_1, &tmp_1);
    modular_subtraction(&result_point->z, &result_point->x, &tmp_3);
    modular_multiplication(&tmp_3, &tmp_2, &tmp_3);
    modular_subtraction(&tmp_3, &tmp_1, &result_point->y);

    modular_addition(&a->z, &b->z, &tmp_1);
    modular_multiplication(&tmp_1, &tmp_1, &tmp_2);
    modular_subtraction(&tmp_2, &tmp_4, &tmp_2);
    modular_subtraction(&tmp_2, &tmp_5, &tmp_2);
    modular_multiplication(&tmp_2, &tmp_0, &result_point->z);
}
