#ifndef BIG_UINT_MULTIPLICATION_HELPER
#define BIG_UINT_MULTIPLICATION_HELPER

// TODO: stop using this. I think I can do the multiplications better

#define UINT64_SUM_WITH_OVERFLOW_FLAG(a, b, result, overflow_flag) \
    do                                                             \
    {                                                              \
        (result) = (a) + (b);                                      \
        (overflow_flag) = ((result) < (b));                        \
    } while (0)

#define ADD_COMPONENT_TO_LIMB(a_limb, b_limb, carry_high_macro_inline, carry_low_macro_inline, result_limb)                                     \
    do                                                                                                                                          \
    {                                                                                                                                           \
        unsigned long long carry_tmp_low_macro_inline, carry_tmp_high_macro_inline, result_tmp_macro_inline;                                    \
                                                                                                                                                \
        UINT64_MULTIPLICATION(a_limb, b_limb, carry_tmp_low_macro_inline, result_tmp_macro_inline);                                             \
                                                                                                                                                \
        UINT64_SUM_WITH_OVERFLOW_FLAG(carry_low_macro_inline, carry_tmp_low_macro_inline, carry_low_macro_inline, carry_tmp_high_macro_inline); \
        carry_high_macro_inline += carry_tmp_high_macro_inline;                                                                                 \
                                                                                                                                                \
        UINT64_SUM_WITH_OVERFLOW_FLAG(result_limb, result_tmp_macro_inline, result_limb, carry_tmp_low_macro_inline);                         \
                                                                                                                                                \
        UINT64_SUM_WITH_OVERFLOW_FLAG(carry_low_macro_inline, carry_tmp_low_macro_inline, carry_low_macro_inline, carry_tmp_high_macro_inline); \
        carry_high_macro_inline += carry_tmp_high_macro_inline;                                                                                 \
    } while (0)

#endif