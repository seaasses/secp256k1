#ifndef UINT64_MULTIPLICATION
#define UINT64_MULTIPLICATION

#include "structs/big_uint.h"

#define uint64_multiplication(a, b, high, low)                                 \
    do                                                                         \
    {                                                                          \
        __uint128_t result_macro_inline = (__uint128_t)(a) * (__uint128_t)(b); \
        (low) = (unsigned long long)(result_macro_inline);                     \
        (high) = (unsigned long long)(result_macro_inline >> 64);              \
    } while (0)

#endif