#include "structs/uint256.h"
#include "unity/unity.h"
#include "constants/secp256k1.h"
#include "modular_operations/modular_multiplication.h"

void test_modular_multiplication_2_3(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {0, 0, 0, 2}};

    Uint256 b = {.limbs = {0, 0, 0, 3}};

    Uint256 expected_result = {.limbs = {0, 0, 0, 6}};

    modular_multiplication(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_modular_multiplication_p_minus_1_times_2(void)
{
    Uint256 result;

    Uint256 a = SECP256K1_P_MINUS_1;

    Uint256 b = {.limbs = {0, 0, 0, 2}};

    Uint256 expected_result = {.limbs = {
                                   0xffffffffffffffff,
                                   0xffffffffffffffff,
                                   0xffffffffffffffff,
                                   0xfffffffefffffc2d,
                               }};

    modular_multiplication(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_modular_multiplication_p_minus_1_times_p_minus_1(void)
{
    Uint256 result;

    Uint256 a = SECP256K1_P_MINUS_1;
    Uint256 b = SECP256K1_P_MINUS_1;

    Uint256 expected_result = {.limbs = {
                                   0, 0, 0, 1}};

    modular_multiplication(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_modular_multiplication_p_minus_1_times_big_number(void)
{
    Uint256 result;

    Uint256 a = SECP256K1_P_MINUS_1;

    Uint256 b = {.limbs = {
                     0x2e91a4f933e5541b,
                     0xfb13b282b7446766,
                     0xdded2edd825d3a88,
                     0xce882f3193a2cf1a,

                 }};

    Uint256 expected_result = {.limbs = {

                                   0xd16e5b06cc1aabe4,
                                   0x04ec4d7d48bb9899,
                                   0x2212d1227da2c577,
                                   0x3177d0cd6c5d2d15,

                               }};

    modular_multiplication(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_modular_multiplication_two_big_numbers(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {

                     0xd3581494b0f922f3,
                     0x393a25c91ad6a490,
                     0x576b611ede5b2abc,
                     0x862ca04e3b094e23,

                 }};

    Uint256 b = {.limbs = {

                     0x76ba21d82455fe6b,
                     0x7b64ece6415bcd77,
                     0xd4dac0601ac6c315,
                     0x6afab7485cc9e83a,

                 }};

    Uint256 expected_result = {.limbs = {

                                   0x4afb731ca87e805c,
                                   0xc69265ad26abed20,
                                   0x171fbbccc022d792,
                                   0x17e71308db5716fc,

                               }};

    modular_multiplication(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}