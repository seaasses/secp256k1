#include "modular_operations/modular_double.h"
#include "uint256/shift_left.h"
#include "uint256/subtraction.h"
#include "constants/secp256k1.h"

inline void modular_double(const Uint256 *a, Uint256 *result) 
{

  // inplace safe

  Uint256 tmp;
  unsigned long tmpBool = a->limbs[0] >> 63; // now tmpBool is 1 if most significant bit is set, 0 otherwise
  uint256_shift_left(a, &tmp);

  // cases:
  // 1. result is less than p: subtract 0
  // 2. result is equal or greater than p but less than 2^256: subtract p
  // 3. result is greater than or equal to 2^256: subtract 2^256

  // so, if most significant bit is 1 (case 2 or 3), we need to subtract p
  // if result is outside of 0 secp256k1, subtract p too

  unsigned long isOutsideSecp256k1Space = 0;
  isOutsideSecp256k1Space |= (tmp.limbs[0] > SECP256K1_P_0);
  isOutsideSecp256k1Space |= ((tmp.limbs[0] == SECP256K1_P_0) & (tmp.limbs[1] > SECP256K1_P_1));
  isOutsideSecp256k1Space |= ((tmp.limbs[0] == SECP256K1_P_0) & (tmp.limbs[1] == SECP256K1_P_1) & (tmp.limbs[2] > SECP256K1_P_2));
  isOutsideSecp256k1Space |= ((tmp.limbs[0] == SECP256K1_P_0) & (tmp.limbs[1] == SECP256K1_P_1) & (tmp.limbs[2] == SECP256K1_P_2) & (tmp.limbs[3] >= SECP256K1_P_3));

  // TODO: test use tmpbool or do the -(|) on the 4 limbs
  tmpBool = -(tmpBool | isOutsideSecp256k1Space);

  const Uint256 toSubtract = {.limbs = {
                                  SECP256K1_P_0 & tmpBool,
                                  SECP256K1_P_1 & tmpBool,
                                  SECP256K1_P_2 & tmpBool,
                                  SECP256K1_P_3 & tmpBool,
                              }};

  uint256_subtraction(&tmp, &toSubtract, result);
}

