#include "constants/secp256k1.h"
#include "modular_operations/modular_addition.h"
#include "modular_operations/modular_double.h"
#include "modular_operations/modular_subtraction.h"
#include "modular_operations/modular_multiplication.h"
#include "modular_operations/modular_exponentiation.h"
#include "secp256k1/double_point.h"

inline void double_point(const Point *point, Point *result_point)
{
    // In teory, this and sumPoints could/should be merged together
    // but in practice, when sumPoints is called, probably the points are not the
    // same. By doing this, we can save a check in sumPoints to see if the points
    // are the same and simplify the code and be more efficient.

    // This function will be used primarily to double a point and implement Point * scalar
    // multiplication

    Uint256 tmp = SECP256K1_P_MINUS_2;

    // LAMBDA = (3x^2 + a) * (2y)^(-1)

    modular_multiplication(&point->x, &point->x, &result_point->y);         // result.y = x^2
    modular_double(&result_point->y, &result_point->x);                     // result.x = 2x^2 and result.y = x^2
    modular_addition(&result_point->y, &result_point->x, &result_point->y); // result.x = 2x^2 and result.y = 3x^2

    modular_double(&point->y, &result_point->x); // result.x = 2y and result.y = 3x^2

    // TODO: This uses Fermat's little theorem to compute the inverse. Create a function to this and test it vs the
    // Extended Euclidean Algorithm

    // add comment about montgomery multiplication
    modular_exponentiation(&result_point->x, &tmp, &result_point->x); // result.x = (2y)^(-1) and result.y = 3x^2

    modular_multiplication(&result_point->y, &result_point->x, &result_point->y); // result.x = (2y)^(-1) and result.y = LAMBDA

    // X_RESULT = LAMBDA^2 - 2x

    modular_double(&point->x, &result_point->x);                      // result.x = 2x and result.y = LAMBDA
    modular_multiplication(&result_point->y, &result_point->y, &tmp); // result.x = 2x, result.y = LAMBDA and tmp = LAMBDA^2
    modular_subtraction(&tmp, &result_point->x, &result_point->x);    // result.x = X_RESULT, result.y = LAMBDA and tmp = LAMBDA^2

    // Y_RESULT = LAMBDA * (x - X_RESULT) - y

    modular_subtraction(&point->x, &result_point->x, &tmp);             // result.x = X_RESULT, tmp = x - X_RESULT and result.y = LAMBDA
    modular_multiplication(&result_point->y, &tmp, &result_point->y);   // result.x = X_RESULT, tmp = x - X_RESULT and result.y = lambda * (x - X_RESULT)
    modular_subtraction(&result_point->y, &point->y, &result_point->y); // result.x = X_RESULT, result.y = Y_RESULT :D
}
