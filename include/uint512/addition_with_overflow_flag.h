#ifndef UINT512_ADDITION_WITH_OVERFLOW_FLAG
#define UINT512_ADDITION_WITH_OVERFLOW_FLAG

#include "structs/uint512.h"

void uint512_addition_with_overflow_flag(const Uint512 *a, const Uint512 *b,
                                         Uint512 *result, unsigned int *overflowFlag);

#endif