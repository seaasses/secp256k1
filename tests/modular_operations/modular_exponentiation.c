#include "structs/uint256.h"
#include "unity/unity.h"
#include "constants/secp256k1.h"
#include "modular_operations/modular_exponentiation.h"

void test_modular_exponentiation_2_3(void)
{
    Uint256 result;

    Uint256 base = {.limbs = {0, 0, 0, 2}};

    Uint256 exponent = {.limbs = {0, 0, 0, 3}};

    Uint256 expected_result = {.limbs = {0, 0, 0, 8}};

    modular_exponentiation(&base, &exponent, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_modular_exponentiation_p_minus_1_power_0(void)
{
    Uint256 result;

    Uint256 base = SECP256K1_P_MINUS_1;

    Uint256 exponent = {.limbs = {

                            0, 0, 0, 0

                        }};

    Uint256 expected_result = {.limbs = {
                                   0, 0, 0, 1

                               }};

    modular_exponentiation(&base, &exponent, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_modular_exponentiation_p_minus_1_power_1(void)
{
    Uint256 result;

    Uint256 base = SECP256K1_P_MINUS_1;

    Uint256 exponent = {.limbs = {

                            0, 0, 0, 1

                        }};

    Uint256 expected_result = SECP256K1_P_MINUS_1;

    modular_exponentiation(&base, &exponent, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_modular_exponentiation_p_minus_1_power_2(void)
{
    Uint256 result;

    Uint256 base = SECP256K1_P_MINUS_1;

    Uint256 exponent = {.limbs = {
                            0, 0, 0, 2}};

    Uint256 expected_result = {.limbs = {
                                   0x0000000000000000,
                                   0x0000000000000000,
                                   0x0000000000000000,
                                   0x0000000000000001,
                               }};

    modular_exponentiation(&base, &exponent, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_modular_exponentiation_p_minus_1_power_3(void)
{
    Uint256 result;

    Uint256 base = SECP256K1_P_MINUS_1;

    Uint256 exponent = {.limbs = {
                            0, 0, 0, 3}};

    Uint256 expected_result = {.limbs = {
                                   0xffffffffffffffff,
                                   0xffffffffffffffff,
                                   0xffffffffffffffff,
                                   0xfffffffefffffc2e,

                               }};

    modular_exponentiation(&base, &exponent, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_modular_exponentiation_p_minus_1_power_p_minus_1(void)
{
    Uint256 result;

    Uint256 base = SECP256K1_P_MINUS_1;
    Uint256 exponent = SECP256K1_P_MINUS_1;

    Uint256 expected_result = {.limbs = {
                                   0, 0, 0, 1}};

    modular_exponentiation(&base, &exponent, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_modular_exponentiation_p_minus_2_power_p_minus_1(void)
{
    Uint256 result;

    Uint256 base = SECP256K1_P_MINUS_2;
    Uint256 exponent = SECP256K1_P_MINUS_1;

    Uint256 expected_result = {.limbs = {
                                   0x0000000000000000,
                                   0x0000000000000000,
                                   0x0000000000000000,
                                   0x0000000000000001,
                               }};

    modular_exponentiation(&base, &exponent, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_modular_exponentiation_p_minus_2_power_p_minus_2(void)
{
    Uint256 result;

    Uint256 base = SECP256K1_P_MINUS_2;
    Uint256 exponent = SECP256K1_P_MINUS_2;

    Uint256 expected_result = {.limbs = {
                                   0x7fffffffffffffff,
                                   0xffffffffffffffff,
                                   0xffffffffffffffff,
                                   0xffffffff7ffffe17,
                               }};

    modular_exponentiation(&base, &exponent, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}
void test_modular_exponentiation_two_big_numbers(void)
{
    Uint256 result;

    Uint256 base = {.limbs = {

                        0x5619934727069f9a,
                        0x1f15b34be4f10fc7,
                        0x90b89c63b3b0db06,
                        0xf694052d4af73940,

                    }};

    Uint256 exponent = {.limbs = {

                            0x2822d9b2180cd916,
                            0x84460c60b6199bc0,
                            0x74e01e7d4995c8ca,
                            0x3172edd6892e5505,

                        }};

    Uint256 expected_result = {.limbs = {

                                   0xfc1dbdb3a7f2476b,
                                   0x27c1ff1070e65ba1,
                                   0x9e41f3d4aedf225e,
                                   0x552ebdf34d0e8b6d,

                               }};

    modular_exponentiation(&base, &exponent, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}
