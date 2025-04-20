#include "uint512/addition_with_overflow_flag.h"

inline void uint512_addition_with_overflow_flag(const Uint512 *a, const Uint512 *b,
                                                Uint512 *result, unsigned int *overflowFlag)
{
  // inplace unsafe
  result->limbs[7] = a->limbs[7] + b->limbs[7];
  unsigned int carry = result->limbs[7] < a->limbs[7];

  result->limbs[6] = a->limbs[6] + b->limbs[6] + carry;
  carry = (result->limbs[6] < a->limbs[6]) | ((result->limbs[6] == a->limbs[6]) & carry);

  result->limbs[5] = a->limbs[5] + b->limbs[5] + carry;
  carry = (result->limbs[5] < a->limbs[5]) | ((result->limbs[5] == a->limbs[5]) & carry);

  result->limbs[4] = a->limbs[4] + b->limbs[4] + carry;
  carry = (result->limbs[4] < a->limbs[4]) | ((result->limbs[4] == a->limbs[4]) & carry);

  result->limbs[3] = a->limbs[3] + b->limbs[3] + carry;
  carry = (result->limbs[3] < a->limbs[3]) | ((result->limbs[3] == a->limbs[3]) & carry);

  result->limbs[2] = a->limbs[2] + b->limbs[2] + carry;
  carry = (result->limbs[2] < a->limbs[2]) | ((result->limbs[2] == a->limbs[2]) & carry);

  result->limbs[1] = a->limbs[1] + b->limbs[1] + carry;
  carry = (result->limbs[1] < a->limbs[1]) | ((result->limbs[1] == a->limbs[1]) & carry);

  result->limbs[0] = a->limbs[0] + b->limbs[0] + carry;
  *overflowFlag = (result->limbs[0] < a->limbs[0]) | ((result->limbs[0] == a->limbs[0]) & carry);
}
