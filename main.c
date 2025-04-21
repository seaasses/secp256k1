#include "unity/unity.h"
#include "tests/uint256/shift_left.c"
#include "tests/uint256/shift_right.c"
#include "tests/uint256/addition_with_overflow_flag.c"
#include "tests/uint256/addition.c"
#include "tests/uint256/subtraction_with_underflow_flag.c"
#include "tests/uint256/subtraction.c"
#include "tests/uint256/multiplication.c"
#include "tests/modular_operations/modular_double.c"
#include "tests/modular_operations/modular_addition.c"
#include "tests/modular_operations/modular_subtraction.c"
#include "tests/modular_operations/modular_multiplication.c"
#include "tests/modular_operations/modular_exponentiation.c"
#include "tests/secp256k1/jacobian_to_affine.c"
#include "tests/secp256k1/jacobian_double_point.c"
#include "tests/secp256k1/g_times_scalar.c"
#include "tests/secp256k1/jacobian_point_addition_jacobian_plus_affine.c"
#include "tests/uint512/addition_with_overflow_flag.c"
#include "tests/montgomery/montgomery_reduction.c"
#include "tests/montgomery/montgomery_multiplication.c"
#include "tests/montgomery/to_montgomery.c"

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

    // subtraction
    RUN_TEST(test_subtraction_1_0);
    RUN_TEST(test_subtraction_1_1);
    RUN_TEST(test_subtraction_3_2);
    RUN_TEST(test_subtraction_borrow_on_limb_3);
    RUN_TEST(test_subtraction_borrow_on_limb_2);
    RUN_TEST(test_subtraction_borrow_on_limb_1);
    RUN_TEST(test_subtraction_0_1_underflow);
    RUN_TEST(test_subtraction_all_bits_set_minus_1);
    RUN_TEST(test_subtraction_all_bits_set_minus_all_bits_set);
    RUN_TEST(test_subtraction_1_0_bits_pattern_minus_0_1_bits_pattern);
    RUN_TEST(test_subtraction_0_1_bits_pattern_minus_1_0_bits_pattern);
    RUN_TEST(test_subtraction_big_numbers_that_underflow);
    RUN_TEST(test_subtraction_big_numbers_that_do_not_underflow);

    // subtraction with underflow flag

    RUN_TEST(test_subtraction_with_underflow_flag_1_0);
    RUN_TEST(test_subtraction_with_underflow_flag_1_1);
    RUN_TEST(test_subtraction_with_underflow_flag_3_2);
    RUN_TEST(test_subtraction_with_underflow_flag_borrow_on_limb_3);
    RUN_TEST(test_subtraction_with_underflow_flag_borrow_on_limb_2);
    RUN_TEST(test_subtraction_with_underflow_flag_borrow_on_limb_1);
    RUN_TEST(test_subtraction_with_underflow_flag_0_1_underflow);
    RUN_TEST(test_subtraction_with_underflow_flag_all_bits_set_minus_1);
    RUN_TEST(test_subtraction_with_underflow_flag_all_bits_set_minus_all_bits_set);
    RUN_TEST(test_subtraction_with_underflow_flag_1_0_bits_pattern_minus_0_1_bits_pattern);
    RUN_TEST(test_subtraction_with_underflow_flag_0_1_bits_pattern_minus_1_0_bits_pattern);
    RUN_TEST(test_subtraction_with_underflow_flag_big_numbers_that_underflow);
    RUN_TEST(test_subtraction_with_underflow_flag_big_numbers_that_do_not_underflow);

    // MODULAR OPERATIONS

    // modular double

    RUN_TEST(test_modular_double_3);
    RUN_TEST(test_modular_double_0);
    RUN_TEST(test_double_bit_between_limbs_3_2);
    RUN_TEST(test_double_bit_between_limbs_2_1);
    RUN_TEST(test_double_bit_between_limbs_1_0);
    RUN_TEST(test_double_just_most_significant_bit_set);
    RUN_TEST(test_double_p_minus_1);
    RUN_TEST(test_double_less_than_max_256_bits_after_doubled);
    RUN_TEST(test_double_0_1_bits_pattern);
    RUN_TEST(test_double_1_0_bits_pattern);
    RUN_TEST(test_double_00_ff_bytes_pattern);
    RUN_TEST(test_double_ff_00_bytes_pattern);
    RUN_TEST(test_double_ffffffffffffffff_0000000000000000_limbs_pattern);
    RUN_TEST(test_double_0000000000000000_ffffffffffffffff_limbs_pattern);
    RUN_TEST(test_double_bit_inside_byte);

    // modular addition

    RUN_TEST(test_modular_addition_1_1);
    RUN_TEST(test_modular_addition_2_3);
    RUN_TEST(test_modular_addition_p_minus_1_plus_1);
    RUN_TEST(test_modular_addition_p_minus_1_plus_2);
    RUN_TEST(test_modular_addition_big_numbers_that_pass_p_but_dont_overflow_256_bits);
    RUN_TEST(test_modular_addition_big_numbers_that_overflow_256_bits);

    // modular subtraction
    RUN_TEST(test_modular_subtraction_1_1);
    RUN_TEST(test_modular_subtraction_3_2);
    RUN_TEST(test_modular_subtraction_p_minus_1_minus_p_minus_1);
    RUN_TEST(test_modular_subtraction_two_big_numbers_that_do_not_underflow);
    RUN_TEST(test_modular_subtraction_two_big_numbers_that_underflow_and_before_modulus_is_more_than_p);
    RUN_TEST(test_modular_subtraction_two_big_numbers_that_underflow_and_before_modulus_is_less_than_p);

    // modular multiplication

    RUN_TEST(test_modular_multiplication_2_3);
    RUN_TEST(test_modular_multiplication_p_minus_1_times_2);
    RUN_TEST(test_modular_multiplication_p_minus_1_times_p_minus_1);
    RUN_TEST(test_modular_multiplication_p_minus_1_times_big_number);
    RUN_TEST(test_modular_multiplication_two_big_numbers);

    // modular exponentiation
    RUN_TEST(test_modular_exponentiation_2_3);
    RUN_TEST(test_modular_exponentiation_p_minus_1_power_0);
    RUN_TEST(test_modular_exponentiation_p_minus_1_power_1);
    RUN_TEST(test_modular_exponentiation_p_minus_1_power_2);
    RUN_TEST(test_modular_exponentiation_p_minus_1_power_3);
    RUN_TEST(test_modular_exponentiation_p_minus_1_power_p_minus_1);
    RUN_TEST(test_modular_exponentiation_p_minus_2_power_p_minus_1);
    RUN_TEST(test_modular_exponentiation_p_minus_2_power_p_minus_2);
    RUN_TEST(test_modular_exponentiation_two_big_numbers);

    // SECP256K1

    // jacobian to affine
    RUN_TEST(test_jacobian_to_affine_z_is_1);
    RUN_TEST(test_jacobian_to_affine_random_point_0);
    RUN_TEST(test_jacobian_to_affine_random_point_1);
    RUN_TEST(test_jacobian_to_affine_random_point_2);
    RUN_TEST(test_jacobian_to_affine_random_point_3);
    RUN_TEST(test_jacobian_to_affine_random_point_4);

    // jacobian double point
    RUN_TEST(test_jacobian_double_point_z_is_1);
    RUN_TEST(test_jacobian_double_random_point_0);
    RUN_TEST(test_jacobian_double_random_point_1);
    RUN_TEST(test_jacobian_double_random_point_2);
    RUN_TEST(test_jacobian_double_random_point_3);

    // g times scalar

    RUN_TEST(test_generator_point_times_1);
    RUN_TEST(test_generator_point_times_big_number_0);
    RUN_TEST(test_generator_point_times_big_number_1);
    RUN_TEST(test_generator_point_times_big_number_2);

    // jacobian point addition jacobian plus affine

    RUN_TEST(test_jacobian_point_addition_jacobian_plus_affine_0);
    RUN_TEST(test_jacobian_point_addition_jacobian_plus_affine_1);
    RUN_TEST(test_jacobian_point_addition_jacobian_plus_affine_2);
    RUN_TEST(test_jacobian_point_addition_jacobian_plus_affine_3);
    RUN_TEST(test_jacobian_point_addition_jacobian_plus_affine_4);

    RUN_TEST(test_multiplication_2_3);
    RUN_TEST(test_multiplication_least_significant_limb_simple_overflow);
    RUN_TEST(test_multiplication_least_significant_limb_max_64_bits_times_max_64_bits);
    RUN_TEST(test_multiplication_least_significant_limb_overflow_random_number);
    RUN_TEST(test_multiplication_limb_2_overflow);
    RUN_TEST(test_multiplication_limb_2_random_2_limbs_numbers_that_carry_to_next_limb);
    RUN_TEST(test_multiplication_2_full_limbs);
    RUN_TEST(test_multiplication_3_full_limbs);
    RUN_TEST(test_multiplication_2_big_numbers_3_limbs_each);
    RUN_TEST(test_multiplication_4_full_limbs);

    // UINT512

    // uint512 addition with overflow flag
    RUN_TEST(test_uint512_addition_with_overflow_flag_2_3);
    RUN_TEST(test_uint512_addition_with_overflow_flag_sum_0);
    RUN_TEST(test_uint512_addition_with_overflow_flag_all_bits_set_plus_1);
    RUN_TEST(test_uint512_addition_with_overflow_flag_all_bits_set_plus_all_bits_set);
    RUN_TEST(test_uint512_addition_with_overflow_flag_most_significant_bit_set_plus_most_significant_bit_set);
    RUN_TEST(test_uint512_addition_with_overflow_flag_without_overflow);
    RUN_TEST(test_uint512_addition_with_overflow_flag_with_overflow);

    // MONTGOMERY

    // montgomery reduction

    RUN_TEST(test_montgomery_reduction_final_n_minus_1);
    RUN_TEST(test_montgomery_reduction_before_mod_n_final_n_minus_1);
    RUN_TEST(test_montgomery_reduction_final_n_minus_1);
    RUN_TEST(test_montgomery_reduction_1_in_montgomery);

    // montgomery multiplication
    RUN_TEST(test_montgomery_multiplication_random_numbers_0);
    RUN_TEST(test_montgomery_multiplication_random_numbers_1);
    RUN_TEST(test_montgomery_multiplication_random_numbers_2);
    RUN_TEST(test_montgomery_multiplication_random_numbers_3);
    RUN_TEST(test_montgomery_multiplication_random_numbers_to_subtract_zero);
    RUN_TEST(test_montgomery_multiplication_random_numbers_5_to_subtract_not_zero);

    // to montgomery

    RUN_TEST(test_to_montgomery_0);
    RUN_TEST(test_to_montgomery_1);
    RUN_TEST(test_to_montgomery_n_minus_1);
    RUN_TEST(test_to_montgomery_r_mod_n);
    RUN_TEST(test_to_montgomery_random_number);

    return UNITY_END();
}