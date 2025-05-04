#ifndef BIG_UINT_MULTIPLICATION_HELPER
#define BIG_UINT_MULTIPLICATION_HELPER

// TODO: stop using this. I think I can do the multiplications better

#define uint64_sum_with_overflow_flag(a, b, result, overflow_flag) \
    do                                                             \
    {                                                              \
        (result) = (a) + (b);                                      \
        (overflow_flag) = ((result) < (b));                        \
    } while (0)

#define add_component_to_limb(a_limb, b_limb, carry_high_macro_inline, carry_low_macro_inline, result_limb)                                     \
    do                                                                                                                                          \
    {                                                                                                                                           \
        unsigned long long carry_tmp_low_macro_inline, carry_tmp_high_macro_inline, result_tmp_macro_inline;                                    \
                                                                                                                                                \
        uint64_multiplication(a_limb, b_limb, carry_tmp_low_macro_inline, result_tmp_macro_inline);                                             \
                                                                                                                                                \
        uint64_sum_with_overflow_flag(carry_low_macro_inline, carry_tmp_low_macro_inline, carry_low_macro_inline, carry_tmp_high_macro_inline); \
        carry_high_macro_inline += carry_tmp_high_macro_inline;                                                                                 \
                                                                                                                                                \
        uint64_sum_with_overflow_flag(result_limb, result_tmp_macro_inline, result_limb, carry_tmp_low_macro_inline);                         \
                                                                                                                                                \
        uint64_sum_with_overflow_flag(carry_low_macro_inline, carry_tmp_low_macro_inline, carry_low_macro_inline, carry_tmp_high_macro_inline); \
        carry_high_macro_inline += carry_tmp_high_macro_inline;                                                                                 \
    } while (0)

#endif