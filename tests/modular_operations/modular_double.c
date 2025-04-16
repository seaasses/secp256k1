#include "structs/uint256.h"
#include "unity/unity.h"
#include "constants/secp256k1.h"
#include "modular_operations/modular_double.h"

void test_modular_double_0(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {0, 0, 0, 0}};

    Uint256 expected_result = {.limbs = {0, 0, 0, 0}};

    modular_double(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_modular_double_3(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {0, 0, 0, 3}};

    Uint256 expected_result = {.limbs = {0, 0, 0, 6}};

    modular_double(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_double_bit_between_limbs_3_2(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {
                     0x0000000000000000,
                     0x0000000000000000,
                     0x0000000000000000,
                     0x8000000000000000,
                 }};

    Uint256 expected_result = {.limbs = {
                                   0x0000000000000000,
                                   0x0000000000000000,
                                   0x0000000000000001,
                                   0x0000000000000000,
                               }};

    modular_double(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_double_bit_between_limbs_2_1(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {
                     0x0000000000000000,
                     0x0000000000000000,
                     0x8000000000000000,
                     0x0000000000000000,
                 }};

    Uint256 expected_result = {.limbs = {
                                   0x0000000000000000,
                                   0x0000000000000001,
                                   0x0000000000000000,
                                   0x0000000000000000,
                               }};

    modular_double(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_double_bit_between_limbs_1_0(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {
                     0x0000000000000000,
                     0x8000000000000000,
                     0x0000000000000000,
                     0x0000000000000000,
                 }};

    Uint256 expected_result = {.limbs = {
                                   0x0000000000000001,
                                   0x0000000000000000,
                                   0x0000000000000000,
                                   0x0000000000000000,
                               }};

    modular_double(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_double_just_most_significant_bit_set(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {
                     0x8000000000000000,
                     0x0000000000000000,
                     0x0000000000000000,
                     0x0000000000000000,
                 }};

    Uint256 expected_result = {.limbs = {
                                   0x0000000000000000,
                                   0x0000000000000000,
                                   0x0000000000000000,
                                   0x00000001000003d1,
                               }};

    modular_double(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_double_p_minus_1(void)
{
    Uint256 result;

    Uint256 a = SECP256K1_P_MINUS_1;

    Uint256 expected_result = {.limbs = {
                                   0xffffffffffffffff,
                                   0xffffffffffffffff,
                                   0xffffffffffffffff,
                                   0xfffffffefffffc2d,
                               }};

    modular_double(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_double_less_than_max_256_bits_after_doubled(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {
                              0x7fffffffffffffff,
                              0xffffffffffffffff,
                              0xffffffffffffffff,
                              0xffffffff7ffffe49,
                          }};

    Uint256 expected_result = {.limbs = {
                                            0x0000000000000000,
                                            0x0000000000000000,
                                            0x0000000000000000,
                                            0x0000000000000063,
                                        }};

    modular_double(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_double_0_1_bits_pattern(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {
                              0b0101010101010101010101010101010101010101010101010101010101010101,
                              0b0101010101010101010101010101010101010101010101010101010101010101,
                              0b0101010101010101010101010101010101010101010101010101010101010101,
                              0b0101010101010101010101010101010101010101010101010101010101010101,
                          }};

    Uint256 expected_result = {.limbs = {
                                            0xaaaaaaaaaaaaaaaa,
                                            0xaaaaaaaaaaaaaaaa,
                                            0xaaaaaaaaaaaaaaaa,
                                            0xaaaaaaaaaaaaaaaa,
                                        }};

    modular_double(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_double_1_0_bits_pattern(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {
                              0b1010101010101010101010101010101010101010101010101010101010101010,
                              0b1010101010101010101010101010101010101010101010101010101010101010,
                              0b1010101010101010101010101010101010101010101010101010101010101010,
                              0b1010101010101010101010101010101010101010101010101010101010101010,
                          }};

    Uint256 expected_result = {.limbs = {
                                            0x5555555555555555,
                                            0x5555555555555555,
                                            0x5555555555555555,
                                            0x5555555655555925,
                                        }};

    modular_double(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_double_00_ff_bytes_pattern(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {
                              0x00FF00FF00FF00FF,
                              0x00FF00FF00FF00FF,
                              0x00FF00FF00FF00FF,
                              0x00FF00FF00FF00FF,
                          }};

    Uint256 expected_result = {.limbs = {
                                            0x01FE01FE01FE01FE,
                                            0x01FE01FE01FE01FE,
                                            0x01FE01FE01FE01FE,
                                            0x01FE01FE01FE01FE,

                                        }};

    modular_double(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_double_ff_00_bytes_pattern(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {
                              0xFF00FF00FF00FF00,
                              0xFF00FF00FF00FF00,
                              0xFF00FF00FF00FF00,
                              0xFF00FF00FF00FF00,
                          }};

    Uint256 expected_result = {.limbs = {
                                            0xfe01fe01fe01fe01,
                                            0xfe01fe01fe01fe01,
                                            0xfe01fe01fe01fe01,
                                            0xfe01fe02fe0201d1,

                                        }};

    modular_double(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_double_ffffffffffffffff_0000000000000000_limbs_pattern(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {
                              0xFFFFFFFFFFFFFFFF,
                              0,
                              0xFFFFFFFFFFFFFFFF,
                              0,
                          }};

    Uint256 expected_result = {.limbs = {
                                            0xfffffffffffffffe,
                                            0x0000000000000001,
                                            0xfffffffffffffffe,
                                            0x00000001000003d1,
                                        }};

    modular_double(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_double_0000000000000000_ffffffffffffffff_limbs_pattern(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {
                              0,
                              0xFFFFFFFFFFFFFFFF,
                              0,
                              0xFFFFFFFFFFFFFFFF,
                          }};

    Uint256 expected_result = {.limbs = {
                                            0x0000000000000001,
                                            0xFFFFFFFFFFFFFFFE,
                                            0x0000000000000001,
                                            0xFFFFFFFFFFFFFFFE,
                                        }};

    modular_double(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_double_bit_inside_byte(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {
                              0b0010000000010000010000000000100000001000000100000101000000001000,
                              0b0000001000000000010000000100010000010000000100000100000000000010,
                              0b0000000100101000000110000100000000000100000000000010000000010000,
                              0b0000001000100000010010000100000000000001000000000100010000001000,
                          }};

    Uint256 expected_result = {.limbs = {
                                            0b0100000000100000100000000001000000010000001000001010000000010000,
                                            0b0000010000000000100000001000100000100000001000001000000000000100,
                                            0b0000001001010000001100001000000000001000000000000100000000100000,
                                            0b0000010001000000100100001000000000000010000000001000100000010000,
                                        }};

    modular_double(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}
