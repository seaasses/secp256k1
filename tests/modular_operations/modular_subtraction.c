#include "structs/uint256.h"
#include "unity/unity.h"
#include "constants/secp256k1.h"
#include "modular_operations/modular_subtraction.h"

void test_modular_subtraction_1_1(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {0, 0, 0, 1}};

    Uint256 b = {.limbs = {0, 0, 0, 1}};

    Uint256 expected_result = {.limbs = {0, 0, 0, 0}};

    modular_subtraction(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_modular_subtraction_3_2(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {0, 0, 0, 3}};

    Uint256 b = {.limbs = {0, 0, 0, 2}};

    Uint256 expected_result = {.limbs = {0, 0, 0, 1}};

    modular_subtraction(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_modular_subtraction_p_minus_1_minus_p_minus_1(void)
{
    Uint256 result;

    Uint256 a = SECP256K1_P_MINUS_1;

    Uint256 b = SECP256K1_P_MINUS_1;

    Uint256 expected_result = {.limbs = {0, 0, 0, 0}};

    modular_subtraction(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_modular_subtraction_two_big_numbers_that_do_not_underflow(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {
                     0x37387cbdcd211b05,
                     0xfd9aa3ba034d82a9,
                     0x33bb4ec109a9c341,
                     0x07c8cf87435c3b59,
                 }};

    Uint256 b = {.limbs = {
                     0x17dacc237e0b7cac,
                     0x0f5df04f06f433ad,
                     0xdd36d7a3b2a50879,
                     0xffc07d246a7c74b0,
                 }};

    Uint256 expected_result = {.limbs = {
                                   0x1f5db09a4f159e59,
                                   0xee3cb36afc594efb,
                                   0x5684771d5704bac7,
                                   0x08085262d8dfc6a9,
                               }};

    modular_subtraction(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_modular_subtraction_two_big_numbers_that_underflow_and_before_modulus_is_more_than_p(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {

                     0x4bf10bd557c9e577,
                     0xaab30d47eee0ef93,
                     0xede4b19a698c09d8,
                     0xd5f3770a8ebf6df5,

                 }};

    Uint256 b = {.limbs = {

                     0x4bf10bd557c9e577,
                     0xaab30d47eee0ef93,
                     0xede4b19a698c09d8,
                     0xd5f3770aabe18ed3,
                 }};

    Uint256 expected_result = {.limbs = {

                                   0xffffffffffffffff,
                                   0xffffffffffffffff,
                                   0xffffffffffffffff,
                                   0xfffffffee2dddb51,

                               }};

    modular_subtraction(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_modular_subtraction_two_big_numbers_that_underflow_and_before_modulus_is_less_than_p(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {

                     0x6bead697fb9ce5d5,
                     0x4f44a0e13339420f,
                     0x1fcf9085d75c925b,
                     0x1fc91aa53e0dc611,

                 }};

    Uint256 b = {.limbs = {

                     0x9f5375d05646ba4b,
                     0xc5d66662751d12f0,
                     0xeabd0c4af7491bba,
                     0x3db1ba97b9fa8cde,

                 }};

    Uint256 expected_result = {.limbs = {

                                   0xcc9760c7a5562b89,
                                   0x896e3a7ebe1c2f1e,
                                   0x3512843ae01376a0,
                                   0xe217600c84133562,

                               }};

    modular_subtraction(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}