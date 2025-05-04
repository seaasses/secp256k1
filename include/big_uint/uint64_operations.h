#ifndef UINT64_OPERATIONS
#define UINT64_OPERATIONS

#define UINT64_MULTIPLICATION(a, b, high, low)                                 \
    do                                                                         \
    {                                                                          \
        __uint128_t result_macro_inline = (__uint128_t)(a) * (__uint128_t)(b); \
        (low) = (unsigned long long)(result_macro_inline);                     \
        (high) = (unsigned long long)(result_macro_inline >> 64);              \
    } while (0)

#define UINT64_SUM_WITH_OVERFLOW_FLAG(a, b, result, overflow_flag) \
    do                                                             \
    {                                                              \
        (result) = (a) + (b);                                      \
        (overflow_flag) = ((result) < (b));                        \
    } while (0)

#endif