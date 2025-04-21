#ifndef MONTGOMERY_CONSTANTS
#define MONTGOMERY_CONSTANTS

#include "constants/secp256k1.h"

#define MONTGOMERY_N SECP256K1_P
#define MONTGOMERY_N_MINUS_2 SECP256K1_P_MINUS_2


#define MONTGOMERY_N_0 SECP256K1_P_0
#define MONTGOMERY_N_1 SECP256K1_P_1
#define MONTGOMERY_N_2 SECP256K1_P_2
#define MONTGOMERY_N_3 SECP256K1_P_3

#define MONTGOMERY_N_PRIME                                                 \
    {.limbs = {0xc9bd190515538399, 0x9c46c2c295f2b761, 0xbcb223fedc24a059, \
               0xd838091dd2253531}}

#define MONTGOMERY_R_SQUARED                                               \
    {.limbs = {0x0000000000000000, 0x0000000000000000, 0x0000000000000001, \
               0x000007a2000e90a1}}

#define ONE_IN_MONTGOMERY                                                  \
    {.limbs = {0x0000000000000000, 0x0000000000000000, 0x0000000000000000, \
               0x00000001000003d1}}

#define ONE_IN_MONTGOMERY_3 0x00000001000003d1

#endif
