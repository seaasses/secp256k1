#ifndef POINT
#define POINT

#include "structs/big_uint.h"

typedef struct
{
    Uint256 x;
    Uint256 y;
} Point;

typedef struct
{
    Uint256 x;
    Uint256 y;
    Uint256 z;
} JacobianPoint;

#endif