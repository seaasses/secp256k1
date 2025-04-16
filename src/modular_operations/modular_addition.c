#include "modular_operations/modular_addition.h"
#include "uint256/shift_left.h"
#include "uint256/subtraction.h"
#include "uint256/addition_with_overflow_flag.h"
#include "constants/secp256k1.h"

inline void modular_addition(const Uint256 *a, const Uint256 *b, Uint256 *result)
{

  // inplace safe
  unsigned int overflowFlag;
  Uint256 tmp;

  uint256_addition_with_overflow_flag(a, b, &tmp, &overflowFlag);

  // cases:
  // 1. less than p : subtract 0 
  // 2. more than p-1 and less than 2^256 : subtract p
  // 3. more than 2^256: subtract p
  // I really do not need to call modulus and can save a subtraction - and turns the function inplace safe without using a temporary variable
  // SO: subtract p when outside secp256k1 space OR overflowFlag is true

  // TODO: create a function to do this. modulus and this (and probably others will) use this
  unsigned long long isOutsideSecp256k1Space = 0;
  isOutsideSecp256k1Space |= (tmp.limbs[0] > SECP256K1_P_0);
  isOutsideSecp256k1Space |= ((tmp.limbs[0] == SECP256K1_P_0) & (tmp.limbs[1] > SECP256K1_P_1));
  isOutsideSecp256k1Space |= ((tmp.limbs[0] == SECP256K1_P_0) & (tmp.limbs[1] == SECP256K1_P_1) & (tmp.limbs[2] > SECP256K1_P_2));
  isOutsideSecp256k1Space |= ((tmp.limbs[0] == SECP256K1_P_0) & (tmp.limbs[1] == SECP256K1_P_1) & (tmp.limbs[2] == SECP256K1_P_2) & (tmp.limbs[3] >= SECP256K1_P_3));

  const unsigned long long toSubtractMask = -(isOutsideSecp256k1Space | ((unsigned long long) overflowFlag));

  const Uint256 toSubtract = (Uint256){.limbs = {
                                           SECP256K1_P_0 & toSubtractMask,
                                           SECP256K1_P_1 & toSubtractMask,
                                           SECP256K1_P_2 & toSubtractMask,
                                           SECP256K1_P_3 & toSubtractMask,
                                       }};

  uint256_subtraction(&tmp, &toSubtract, result);
}
