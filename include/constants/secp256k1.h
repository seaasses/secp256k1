#ifndef SECP256K1_CONSTANTS
#define SECP256K1_CONSTANTS

#include "structs/uint256.h"

#define SECP256K1_P                                                        \
    {.limbs = {0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, \
               0xFFFFFFFEFFFFFC2F}}

#define SECP256K1_P_MINUS_1                                                \
    {.limbs = {0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, \
               0xFFFFFFFEFFFFFC2E}}

#define SECP256K1_P_MINUS_2                                                \
    {.limbs = {0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, \
               0xFFFFFFFEFFFFFC2D}}

#define SECP256K1_P_0 0xFFFFFFFFFFFFFFFF
#define SECP256K1_P_1 0xFFFFFFFFFFFFFFFF
#define SECP256K1_P_2 0xFFFFFFFFFFFFFFFF
#define SECP256K1_P_3 0xFFFFFFFEFFFFFC2F

#endif