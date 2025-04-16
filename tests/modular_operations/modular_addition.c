#include "structs/uint256.h"
#include "unity/unity.h"
#include "constants/secp256k1.h"
#include "modular_operations/modular_addition.h"

void test_modular_addition_1_1(void)
{
    Uint256 result;

    Uint256 a = (Uint256){.limbs = {0, 0, 0, 1}};

    Uint256 b = (Uint256){.limbs = {0, 0, 0, 1}};

    Uint256 expected_result = (Uint256){.limbs = {0, 0, 0, 2}};

    modular_addition(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_modular_addition_2_3(void)
{
    Uint256 result;

    Uint256 a = (Uint256){.limbs = {0, 0, 0, 2}};

    Uint256 b = (Uint256){.limbs = {0, 0, 0, 3}};

    Uint256 expected_result = (Uint256){.limbs = {0, 0, 0, 5}};

    modular_addition(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_modular_addition_p_minus_1_plus_1(void)
{
    Uint256 result;

    Uint256 a = SECP256K1_P_MINUS_1;

    Uint256 b = (Uint256){.limbs = {0, 0, 0, 1}};

    Uint256 expected_result = (Uint256){.limbs = {0, 0, 0, 0}};

    modular_addition(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_modular_addition_p_minus_1_plus_2(void)
{
    Uint256 result;

    Uint256 a = SECP256K1_P_MINUS_1;

    Uint256 b = (Uint256){.limbs = {0, 0, 0, 2}};

    Uint256 expected_result = (Uint256){.limbs = {0, 0, 0, 1}};

    modular_addition(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_modular_addition_big_numbers_that_pass_p_but_dont_overflow_256_bits(void)
{
    Uint256 result;

    Uint256 a = (Uint256){.limbs = {
                              0xf348f7df5fdba0de,
                              0x804dea1343dc2f6d,
                              0xb765cf9e555c77a2,
                              0x083b8a2107e673f7,
                          }};

    Uint256 b = (Uint256){.limbs = {
                              0x0cb70820a0245f21,
                              0x7fb215ecbc23d092,
                              0x489a3061aaa3885d,
                              0xf7c475deeb641cf2,
                          }};

    Uint256 expected_result = (Uint256){.limbs = {
                                            0x0000000000000000,
                                            0x0000000000000000,
                                            0x0000000000000000,
                                            0x00000000f34a94ba,
                                        }};

    modular_addition(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_modular_addition_big_numbers_that_overflow_256_bits(void)
{
    Uint256 result;

    Uint256 a = (Uint256){.limbs = {
                              0xa51d7ec77144983b,
                              0xceba079e66c38dd6,
                              0x7b33c157505d33be,
                              0x48a657d7211f6c13,
                          }};

    Uint256 b = (Uint256){.limbs = {
                              0xc44448692f9f3ad8,
                              0xd32592eebab7989e,
                              0xb9e1556eb5b29bdf,
                              0xa152173e013fa4c2,
                          }};

    Uint256 expected_result = (Uint256){.limbs = {
                                            0x6961c730a0e3d314,
                                            0xa1df9a8d217b2675,
                                            0x351516c6060fcf9d,
                                            0xe9f86f16225f14a6,
                                        }};

    modular_addition(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}