#include "constants/secp256k1.h"
#include "modular_operations/modular_addition.h"
#include "modular_operations/modular_double.h"
#include "modular_operations/modular_subtraction.h"
#include "modular_operations/modular_multiplication.h"
#include "modular_operations/modular_exponentiation.h"
#include "secp256k1/point_addition.h"

inline void point_addition(const Point *point_a, const Point *point_b, Point *result_point)
{
    // JUST FOR a != b, a != -b and both points are not the point at infinity

    Uint256 tmp = SECP256K1_P_MINUS_2;

    // LAMBDA = (y2 - y1) / (x2 - x1)

    modular_subtraction(&point_b->y, &point_a->y, &result_point->y);  // tmp = p-2, result.y = y2 - y1
    modular_subtraction(&point_b->x, &point_a->x, &result_point->x);  // tmp = p-2, result.x = x2 - x1 and result.y = y2 - y1
    modular_exponentiation(&result_point->x, &tmp, &result_point->x); // tmp = p-2, result.x = (x2 - x1)^(-1) and result.y = y2 - y1
    modular_multiplication(&result_point->x, &result_point->y, &tmp); // tmp = LAMBDA, result.x = (x2 - x1)^(-1) and result.y = y2 - y1

    // X_RESULT = LAMBDA^2 - x1 - x2

    modular_multiplication(&tmp, &tmp, &result_point->x);                 // tmp = LAMBDA, result.x = LAMBDA^2, result.y = y2 - y1
    modular_subtraction(&result_point->x, &point_a->x, &result_point->x); // tmp = LAMBDA, result.x = LAMBDA^2 - x1, result.y = y2 - y1
    modular_subtraction(&result_point->x, &point_b->x, &result_point->x); // tmp = LAMBDA, result.x = X_RESULT, result.y = y2 - y1

    // // Y_RESULT = LAMBDA * (x1 ​− ​X_RESULT) − y1

    modular_subtraction(&point_a->x, &result_point->x, &result_point->y); // tmp = LAMBDA, result.x = X_RESULT, result.y = x1 - X_RESULT
    modular_multiplication(&result_point->y, &tmp, &result_point->y);     // tmp = LAMBDA, result.x = X_RESULT, result.y = LAMBDA * (x1 - X_RESULT)
    modular_subtraction(&result_point->y, &point_a->y, &result_point->y); // tmp = LAMBDA, result.x = X_RESULT, result.y = Y_RESULT :D
}
