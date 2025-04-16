#include "structs/uint256.h"
#include "unity/unity.h"
#include "uint256/addition_with_overflow_flag.h"

void test_addition_with_overflow_flag_2_3(void)
{
    Uint256 result;
    unsigned int overflow_flag;

    Uint256 a = {.limbs = {0, 0, 0, 2}};
    Uint256 b = {.limbs = {0, 0, 0, 3}};

    Uint256 expected_result = {.limbs = {0, 0, 0, 5}};

    uint256_addition_with_overflow_flag(&a, &b, &result, &overflow_flag);

    ASSERT_UINT256_EQUAL(expected_result, result);
    TEST_ASSERT_EQUAL_UINT32(0, overflow_flag);
}

void test_addition_with_overflow_flag_carry_on_limb_3(void)
{
    Uint256 result;
    unsigned int overflow_flag;

    Uint256 a = {.limbs = {
                              0x0000000000000000,
                              0x0000000000000000,
                              0x0000000000000000,
                              0x8000000000000000,

                          }};
    Uint256 b = {.limbs = {

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

    uint256_addition_with_overflow_flag(&a, &b, &result, &overflow_flag);

    ASSERT_UINT256_EQUAL(expected_result, result);
    TEST_ASSERT_EQUAL_UINT32(0, overflow_flag);
}

void test_addition_with_overflow_flag_carry_on_limb_2(void)
{
    Uint256 result;
    unsigned int overflow_flag;

    Uint256 a = {.limbs = {

                              0x0000000000000000,
                              0x0000000000000000,
                              0x8000000000000000,
                              0x0000000000000000,
                          }};
    Uint256 b = {.limbs = {
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

    uint256_addition_with_overflow_flag(&a, &b, &result, &overflow_flag);

    ASSERT_UINT256_EQUAL(expected_result, result);
    TEST_ASSERT_EQUAL_UINT32(0, overflow_flag);
}

void test_addition_with_overflow_flag_carry_on_limb_1(void)
{
    Uint256 result;
    unsigned int overflow_flag;

    Uint256 a = {.limbs = {

                              0x0000000000000000,
                              0x8000000000000000,
                              0x0000000000000000,
                              0x0000000000000000,
                          }};
    Uint256 b = {.limbs = {
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

    uint256_addition_with_overflow_flag(&a, &b, &result, &overflow_flag);

    ASSERT_UINT256_EQUAL(expected_result, result);
    TEST_ASSERT_EQUAL_UINT32(0, overflow_flag);
}

void test_addition_with_overflow_flag_overflow(void)
{
    Uint256 result;
    unsigned int overflow_flag;

    Uint256 a = {.limbs = {
                              0x8000000000000000,
                              0x0000000000000000,
                              0x0000000000000000,
                              0x0000000000000000,
                          }};
    Uint256 b = {.limbs = {
                              0x8000000000000000,
                              0x0000000000000000,
                              0x0000000000000000,
                              0x0000000000000000,

                          }};

    Uint256 expected_result = {.limbs = {
                                            0, 0, 0, 0}};

    uint256_addition_with_overflow_flag(&a, &b, &result, &overflow_flag);

    ASSERT_UINT256_EQUAL(expected_result, result);
    TEST_ASSERT_EQUAL_UINT32(1, overflow_flag);
}

void test_addition_with_overflow_flag_all_bits_set_plus_1(void)
{
    Uint256 result;
    unsigned int overflow_flag;

    Uint256 a = {.limbs = {
                              0xFFFFFFFFFFFFFFFF,
                              0xFFFFFFFFFFFFFFFF,
                              0xFFFFFFFFFFFFFFFF,
                              0xFFFFFFFFFFFFFFFF,
                          }};
    Uint256 b = {.limbs = {
                              0, 0, 0, 1}};

    Uint256 expected_result = {.limbs = {
                                            0, 0, 0, 0}};

    uint256_addition_with_overflow_flag(&a, &b, &result, &overflow_flag);

    ASSERT_UINT256_EQUAL(expected_result, result);
    TEST_ASSERT_EQUAL_UINT32(1, overflow_flag);
}

void test_addition_with_overflow_flag_all_bits_set_plus_all_bits_set(void)
{
    Uint256 result;
    unsigned int overflow_flag;

    Uint256 a = {.limbs = {
                              0xFFFFFFFFFFFFFFFF,
                              0xFFFFFFFFFFFFFFFF,
                              0xFFFFFFFFFFFFFFFF,
                              0xFFFFFFFFFFFFFFFF,
                          }};
    Uint256 b = {.limbs = {
                              0xFFFFFFFFFFFFFFFF,
                              0xFFFFFFFFFFFFFFFF,
                              0xFFFFFFFFFFFFFFFF,
                              0xFFFFFFFFFFFFFFFF,
                          }};

    Uint256 expected_result = {.limbs = {
                                            0xFFFFFFFFFFFFFFFF,
                                            0xFFFFFFFFFFFFFFFF,
                                            0xFFFFFFFFFFFFFFFF,
                                            0xFFFFFFFFFFFFFFFE,
                                        }};

    uint256_addition_with_overflow_flag(&a, &b, &result, &overflow_flag);

    ASSERT_UINT256_EQUAL(expected_result, result);
    TEST_ASSERT_EQUAL_UINT32(1, overflow_flag);
}

void test_addition_with_overflow_flag_0_1_bits_pattern_plus_0_1_bits_pattern(void)
{
    Uint256 result;
    unsigned int overflow_flag;

    Uint256 a = {.limbs = {
                              0b0101010101010101010101010101010101010101010101010101010101010101,
                              0b0101010101010101010101010101010101010101010101010101010101010101,
                              0b0101010101010101010101010101010101010101010101010101010101010101,
                              0b0101010101010101010101010101010101010101010101010101010101010101,
                          }};
    Uint256 b = {.limbs = {
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

    uint256_addition_with_overflow_flag(&a, &b, &result, &overflow_flag);

    ASSERT_UINT256_EQUAL(expected_result, result);
    TEST_ASSERT_EQUAL_UINT32(0, overflow_flag);
}

void test_addition_with_overflow_flag_1_0_bits_pattern_plus_1_0_bits_pattern(void)
{
    Uint256 result;
    unsigned int overflow_flag;

    Uint256 a = {.limbs = {
                              0b1010101010101010101010101010101010101010101010101010101010101010,
                              0b1010101010101010101010101010101010101010101010101010101010101010,
                              0b1010101010101010101010101010101010101010101010101010101010101010,
                              0b1010101010101010101010101010101010101010101010101010101010101010,
                          }};
    Uint256 b = {.limbs = {
                              0b1010101010101010101010101010101010101010101010101010101010101010,
                              0b1010101010101010101010101010101010101010101010101010101010101010,
                              0b1010101010101010101010101010101010101010101010101010101010101010,
                              0b1010101010101010101010101010101010101010101010101010101010101010,
                          }};

    Uint256 expected_result = {.limbs = {
                                            0x5555555555555555,
                                            0x5555555555555555,
                                            0x5555555555555555,
                                            0x5555555555555554,

                                        }};

    uint256_addition_with_overflow_flag(&a, &b, &result, &overflow_flag);

    ASSERT_UINT256_EQUAL(expected_result, result);
    TEST_ASSERT_EQUAL_UINT32(1, overflow_flag);
}

void test_addition_with_overflow_flag_1_0_bits_pattern_plus_0_1_bits_pattern(void)
{
    Uint256 result;
    unsigned int overflow_flag;

    Uint256 a = {.limbs = {
                              0b1010101010101010101010101010101010101010101010101010101010101010,
                              0b1010101010101010101010101010101010101010101010101010101010101010,
                              0b1010101010101010101010101010101010101010101010101010101010101010,
                              0b1010101010101010101010101010101010101010101010101010101010101010,
                          }};
    Uint256 b = {.limbs = {
                              0b0101010101010101010101010101010101010101010101010101010101010101,
                              0b0101010101010101010101010101010101010101010101010101010101010101,
                              0b0101010101010101010101010101010101010101010101010101010101010101,
                              0b0101010101010101010101010101010101010101010101010101010101010101,
                          }};

    Uint256 expected_result = {.limbs = {
                                            0xffffffffffffffff,
                                            0xffffffffffffffff,
                                            0xffffffffffffffff,
                                            0xffffffffffffffff,
                                        }};

    uint256_addition_with_overflow_flag(&a, &b, &result, &overflow_flag);

    ASSERT_UINT256_EQUAL(expected_result, result);
    TEST_ASSERT_EQUAL_UINT32(0, overflow_flag);
}

void test_addition_with_overflow_flag_big_numbers_that_overflow(void)
{
    Uint256 result;
    unsigned int overflow_flag;

    Uint256 a = {.limbs = {
                              0xf135b95987fcb540,
                              0x07e03a04d6296d0f,
                              0xa30300ebf31a5164,
                              0x20fbbe18b885968a,
                          }};
    Uint256 b = {.limbs = {
                              0x1a948a63b85b744f,
                              0x40126f005ca48028,
                              0xbabc684af3d97446,
                              0xb395743f498d4657,
                          }};

    Uint256 expected_result = {.limbs = {
                                            0x0bca43bd4058298f,
                                            0x47f2a90532cded38,
                                            0x5dbf6936e6f3c5aa,
                                            0xd49132580212dce1,
                                        }};

    uint256_addition_with_overflow_flag(&a, &b, &result, &overflow_flag);

    ASSERT_UINT256_EQUAL(expected_result, result);
    TEST_ASSERT_EQUAL_UINT32(1, overflow_flag);
}

void test_addition_with_overflow_flag_big_numbers_that_do_not_overflow(void)
{
    Uint256 result;
    unsigned int overflow_flag;

    Uint256 a = {.limbs = {
                              0x053813532ee48e08,
                              0x00b6254e5cfaea21,
                              0x96ec385566de51f5,
                              0xe86807d4c92807c1,
                          }};
    Uint256 b = {.limbs = {
                              0xeddc5071f04c624d,
                              0x99233ea030fb6b97,
                              0xd341c5862ceccb47,
                              0xca0f67c7ec486aae,
                          }};

    Uint256 expected_result = {.limbs = {
                                            0xf31463c51f30f055,
                                            0x99d963ee8df655b9,
                                            0x6a2dfddb93cb1d3d,
                                            0xb2776f9cb570726f,
                                        }};

    uint256_addition_with_overflow_flag(&a, &b, &result, &overflow_flag);

    ASSERT_UINT256_EQUAL(expected_result, result);
    TEST_ASSERT_EQUAL_UINT32(0, overflow_flag);
}
