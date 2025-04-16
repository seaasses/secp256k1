#include "unity/unity.h"
#include "tests/uint256/shift_left.c"
#include "tests/uint256/shift_right.c"
#include "tests/uint256/addition_with_overflow_flag.c"
#include "tests/uint256/addition.c"

#include <stdio.h>
#include <stdint.h>

int main(void)
{
    UNITY_BEGIN();

    // UINT256

    // shift_left
    RUN_TEST(test_shift_left_0);
    RUN_TEST(test_shift_left_1);
    RUN_TEST(test_shift_left_between_limbs_3_2);
    RUN_TEST(test_shift_left_between_limbs_2_1);
    RUN_TEST(test_shift_left_between_limbs_1_0);
    RUN_TEST(test_shift_left_lose_more_significant_bit);
    RUN_TEST(test_shift_left_all_1s);
    RUN_TEST(test_shift_left_0_1_bits_pattern);
    RUN_TEST(test_shift_left_1_0_bits_pattern);
    RUN_TEST(test_shift_left_0_ff_bytes_pattern);
    RUN_TEST(test_shift_left_ff_00_bytes_pattern);
    RUN_TEST(test_shift_left_ffffffffffffffff_0000000000000000_limbs_pattern);
    RUN_TEST(test_shift_left_0000000000000000_ffffffffffffffff_limbs_pattern);
    RUN_TEST(test_shift_left_bit_inside_byte);
    RUN_TEST(test_shift_left_big_number);

    // shift right

    RUN_TEST(test_shift_right_0);
    RUN_TEST(test_shift_right_1);
    RUN_TEST(test_shift_right_between_limbs_0_1);
    RUN_TEST(test_shift_right_between_limbs_1_2);
    RUN_TEST(test_shift_right_between_limbs_2_3);
    RUN_TEST(test_shift_right_lose_least_significant_bit);
    RUN_TEST(test_shift_right_all_1s);
    RUN_TEST(test_shift_right_0_1_bits_pattern);
    RUN_TEST(test_shift_right_1_0_bits_pattern);
    RUN_TEST(test_shift_right_0_ff_bytes_pattern);
    RUN_TEST(test_shift_right_ff_00_bytes_pattern);
    RUN_TEST(test_shift_right_ffffffffffffffff_0000000000000000_limbs_pattern);
    RUN_TEST(test_shift_right_0000000000000000_ffffffffffffffff_limbs_pattern);
    RUN_TEST(test_shift_right_bit_inside_byte);
    RUN_TEST(test_shift_right_big_number);

    // addition
    RUN_TEST(test_addition_2_3);
    RUN_TEST(test_addition_carry_on_limb_3);
    RUN_TEST(test_addition_carry_on_limb_2);
    RUN_TEST(test_addition_carry_on_limb_1);
    RUN_TEST(test_addition_overflow);
    RUN_TEST(test_addition_all_bits_set_plus_1);
    RUN_TEST(test_addition_all_bits_set_plus_all_bits_set);
    RUN_TEST(test_addition_0_1_bits_pattern_plus_0_1_bits_pattern);
    RUN_TEST(test_addition_1_0_bits_pattern_plus_1_0_bits_pattern);
    RUN_TEST(test_addition_1_0_bits_pattern_plus_0_1_bits_pattern);
    RUN_TEST(test_addition_big_numbers_that_overflow);
    RUN_TEST(test_addition_big_numbers_that_do_not_overflow);

    // addition with overflow flag
    RUN_TEST(test_addition_with_overflow_flag_2_3);
    RUN_TEST(test_addition_with_overflow_flag_carry_on_limb_3);
    RUN_TEST(test_addition_with_overflow_flag_carry_on_limb_2);
    RUN_TEST(test_addition_with_overflow_flag_carry_on_limb_1);
    RUN_TEST(test_addition_with_overflow_flag_overflow);
    RUN_TEST(test_addition_with_overflow_flag_all_bits_set_plus_1);
    RUN_TEST(test_addition_with_overflow_flag_all_bits_set_plus_all_bits_set);
    RUN_TEST(test_addition_with_overflow_flag_0_1_bits_pattern_plus_0_1_bits_pattern);
    RUN_TEST(test_addition_with_overflow_flag_1_0_bits_pattern_plus_1_0_bits_pattern);
    RUN_TEST(test_addition_with_overflow_flag_1_0_bits_pattern_plus_0_1_bits_pattern);
    RUN_TEST(test_addition_with_overflow_flag_big_numbers_that_overflow);
    RUN_TEST(test_addition_with_overflow_flag_big_numbers_that_do_not_overflow);

    return UNITY_END();
}