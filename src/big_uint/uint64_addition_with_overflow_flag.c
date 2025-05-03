#include "big_uint/uint64_addition_with_overflow_flag.h"

inline void uint64_addition_with_overflow_flag(unsigned long long a, unsigned long long b, unsigned long long *result, unsigned long long *overflow_flag)
{
    *result = a + b;
    *overflow_flag = *result < a;
}
