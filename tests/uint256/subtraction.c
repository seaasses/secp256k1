#include "structs/uint256.h"
#include "unity/unity.h"
#include "uint256/subtraction.h"

void test_subtraction_1_0(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {0, 0, 0, 1}};
    Uint256 b = {.limbs = {0, 0, 0, 0}};

    Uint256 expected_result = {.limbs = {0, 0, 0, 1}};

    uint256_subtraction(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_subtraction_1_1(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {0, 0, 0, 1}};
    Uint256 b = {.limbs = {0, 0, 0, 1}};

    Uint256 expected_result = {.limbs = {0, 0, 0, 0}};

    uint256_subtraction(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_subtraction_3_2(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {0, 0, 0, 3}};
    Uint256 b = {.limbs = {0, 0, 0, 2}};

    Uint256 expected_result = {.limbs = {0, 0, 0, 1}};

    uint256_subtraction(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_subtraction_borrow_on_limb_3(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {
                              0x0000000000000000,
                              0x0000000000000000,
                              0x0000000000000001,
                              0x0000000000000000,
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
                                            0x0000000000000000,
                                            0x8000000000000000,
                                        }};

    uint256_subtraction(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_subtraction_borrow_on_limb_2(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {
                              0x0000000000000000,
                              0x0000000000000001,
                              0x0000000000000000,
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
                                            0x0000000000000000,
                                            0x8000000000000000,
                                            0x0000000000000000,
                                        }};

    uint256_subtraction(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_subtraction_borrow_on_limb_1(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {
                              0x0000000000000001,
                              0x0000000000000000,
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
                                            0x0000000000000000,
                                            0x8000000000000000,
                                            0x0000000000000000,
                                            0x0000000000000000,
                                        }};

    uint256_subtraction(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_subtraction_0_1_underflow(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {0, 0, 0, 0}};
    Uint256 b = {.limbs = {0, 0, 0, 1}};

    Uint256 expected_result = {.limbs = {
                                            0xFFFFFFFFFFFFFFFF,
                                            0xFFFFFFFFFFFFFFFF,
                                            0xFFFFFFFFFFFFFFFF,
                                            0xFFFFFFFFFFFFFFFF,

                                        }};

    uint256_subtraction(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_subtraction_all_bits_set_minus_1(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {
                              0xFFFFFFFFFFFFFFFF,
                              0xFFFFFFFFFFFFFFFF,
                              0xFFFFFFFFFFFFFFFF,
                              0xFFFFFFFFFFFFFFFF,
                          }};
    Uint256 b = {.limbs = {0, 0, 0, 1}};

    Uint256 expected_result = {.limbs = {
                                            0xFFFFFFFFFFFFFFFF,
                                            0xFFFFFFFFFFFFFFFF,
                                            0xFFFFFFFFFFFFFFFF,
                                            0xFFFFFFFFFFFFFFFE,
                                        }};

    uint256_subtraction(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_subtraction_all_bits_set_minus_all_bits_set(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {
                              0xFFFFFFFFFFFFFFFF,
                              0xFFFFFFFFFFFFFFFF,
                              0xFFFFFFFFFFFFFFFF,
                              0xFFFFFFFFFFFFFFFE,
                          }};
    Uint256 b = {.limbs = {
                              0xFFFFFFFFFFFFFFFF,
                              0xFFFFFFFFFFFFFFFF,
                              0xFFFFFFFFFFFFFFFF,
                              0xFFFFFFFFFFFFFFFE,
                          }};

    Uint256 expected_result = {.limbs = {0, 0, 0, 0}};

    uint256_subtraction(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_subtraction_1_0_bits_pattern_minus_0_1_bits_pattern(void)
{
    Uint256 result;

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
                                            0x5555555555555555,
                                            0x5555555555555555,
                                            0x5555555555555555,
                                            0x5555555555555555,
                                        }};

    uint256_subtraction(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_subtraction_0_1_bits_pattern_minus_1_0_bits_pattern(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {
                              0b0101010101010101010101010101010101010101010101010101010101010101,
                              0b0101010101010101010101010101010101010101010101010101010101010101,
                              0b0101010101010101010101010101010101010101010101010101010101010101,
                              0b0101010101010101010101010101010101010101010101010101010101010101,
                          }};

    Uint256 b = {.limbs = {
                              0b1010101010101010101010101010101010101010101010101010101010101010,
                              0b1010101010101010101010101010101010101010101010101010101010101010,
                              0b1010101010101010101010101010101010101010101010101010101010101010,
                              0b1010101010101010101010101010101010101010101010101010101010101010,
                          }};

    Uint256 expected_result = {.limbs = {
                                            0xaaaaaaaaaaaaaaaa,
                                            0xaaaaaaaaaaaaaaaa,
                                            0xaaaaaaaaaaaaaaaa,
                                            0xaaaaaaaaaaaaaaab,
                                        }};

    uint256_subtraction(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_subtraction_big_numbers_that_underflow(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {
                              0xa99c2c080793f4d2,
                              0x97512d1f1589add2,
                              0x0a84e2b3cc062b7b,
                              0x2e91ed0e831b1102,
                          }};
    Uint256 b = {.limbs = {
                              0xf3b5fa6f74e5cb70,
                              0x2ded21f1cde8de6a,
                              0x91d5947b3976bd4a,
                              0x607137d9b3815ce7,
                          }};

    Uint256 expected_result = {.limbs = {
                                            0xb5e6319892ae2962,
                                            0x69640b2d47a0cf67,
                                            0x78af4e38928f6e30,
                                            0xce20b534cf99b41b,
                                        }};

    uint256_subtraction(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_subtraction_big_numbers_that_do_not_underflow(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {
                              0x1d1cafef4ea8f91a,
                              0xf8f29e314e002788,
                              0xf427eb63306aa3eb,
                              0xe84bfd31a5c8cb7e,
                          }};
    Uint256 b = {.limbs = {
                              0x10db8b324fda2d85,
                              0x7b3a898e33ebec1d,
                              0x734c53049084ee2c,
                              0x6a6241ea65d742c4,
                          }};

    Uint256 expected_result = {.limbs = {
                                            0x0c4124bcfececb95,
                                            0x7db814a31a143b6b,
                                            0x80db985e9fe5b5bf,
                                            0x7de9bb473ff188ba,
                                        }};

    uint256_subtraction(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}