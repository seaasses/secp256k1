#include "secp256k1/jacobian_montgomery_to_affine.h"
#include "structs/big_uint.h"
#include "montgomery/montgomery_multiplication.h"
#include "montgomery/montgomery_inverse.h"
#include "montgomery/from_montgomery.h"
#include "constants/secp256k1.h"

inline void jacobian_montgomery_to_affine(const JacobianPoint *point_jac_mont, Point *point)
{
    /*
    POINT_JAC_MONT = (
        X = (x_jac * R mod p)
        Y = (y_jac * R mod p)
        Z = (z_jac * R mod p)
    )

    RESULT = POINT = (
        X = x
        Y = y
    )

    */

    montgomery_inverse(&point_jac_mont->z, &point->y);

    montgomery_multiplication(&point->y, &point->y, &point->x);
    montgomery_multiplication(&point->y, &point->y, &point->x);
    montgomery_multiplication(&point->x, &point->y, &point->y);

    montgomery_multiplication(&point->x, &point_jac_mont->x, &point->x);
    montgomery_multiplication(&point->y, &point_jac_mont->y, &point->y);

    // at this point. The point is affine, but using montgomery representation of integer

    from_montgomery(&point->x, &point->x);
    from_montgomery(&point->y, &point->y);
}