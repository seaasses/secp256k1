#include "unity/unity.h"
#include "tests/uint256/shift_left.c"

#include <stdio.h>
#include <stdint.h>

int main(void)
{
    UNITY_BEGIN();

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



    return UNITY_END();
}