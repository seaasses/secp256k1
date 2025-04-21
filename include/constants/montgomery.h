#ifndef MONTGOMERY_CONSTANTS
#define MONTGOMERY_CONSTANTS

#include "constants/secp256k1.h"

#define MONTGOMERY_N SECP256K1_P
#define MONTGOMERY_N_0 SECP256K1_P_0
#define MONTGOMERY_N_1 SECP256K1_P_1
#define MONTGOMERY_N_2 SECP256K1_P_2
#define MONTGOMERY_N_3 SECP256K1_P_3


#define MONTGOMERY_N_PRIME                                                 \
    {.limbs = {0xc9bd190515538399, 0x9c46c2c295f2b761, 0xbcb223fedc24a059, \
               0xd838091dd2253531}}

#endif