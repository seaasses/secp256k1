#include "big_uint/uint320_uint256_addition.h"
#include "unity/unity.h"

void test_uint320_uint256_addition_3_plus_4(void)
{
    Uint320 result;

    Uint320 a = {.limbs = {0, 0, 0, 0, 3}};
    Uint256 b = {.limbs = {0, 0, 0, 4}};

    Uint320 expected_result = {.limbs = {0, 0, 0, 0, 7}};

    uint320_uint256_addition(&a, &b, &result);

    ASSERT_UINT320_EQUAL(expected_result, result);
}

void test_uint320_uint256_addition_max_320_bits_plus_1(void)
{
    Uint320 result;

    Uint320 a = {.limbs = {0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF}};
    Uint256 b = {.limbs = {0, 0, 0, 1}};

    Uint320 expected_result = {.limbs = {0, 0, 0, 0, 0}};

    uint320_uint256_addition(&a, &b, &result);

    ASSERT_UINT320_EQUAL(expected_result, result);
}

void test_uint320_uint256_addition_max_64_bits_bits_plus_1(void)
{
    Uint320 result;

    Uint320 a = {.limbs = {0, 0, 0, 0, 0xFFFFFFFFFFFFFFFF}};
    Uint256 b = {.limbs = {0, 0, 0, 1}};

    Uint320 expected_result = {.limbs = {0, 0, 0, 1, 0}};

    uint320_uint256_addition(&a, &b, &result);

    ASSERT_UINT320_EQUAL(expected_result, result);
}

void test_uint320_uint256_addition_max_128_bits_bits_plus_1(void)
{
    Uint320 result;

    Uint320 a = {.limbs = {0, 0, 0, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF}};
    Uint256 b = {.limbs = {0, 0, 0, 1}};

    Uint320 expected_result = {.limbs = {0, 0, 1, 0, 0}};

    uint320_uint256_addition(&a, &b, &result);

    ASSERT_UINT320_EQUAL(expected_result, result);
}

void test_uint320_uint256_addition_max_192_bits_bits_plus_1(void)
{
    Uint320 result;

    Uint320 a = {.limbs = {0, 0, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF}};
    Uint256 b = {.limbs = {0, 0, 0, 1}};

    Uint320 expected_result = {.limbs = {0, 1, 0, 0, 0}};

    uint320_uint256_addition(&a, &b, &result);

    ASSERT_UINT320_EQUAL(expected_result, result);
}

void test_uint320_uint256_addition_max_256_bits_bits_plus_1(void)
{
    Uint320 result;

    Uint320 a = {.limbs = {0, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF}};
    Uint256 b = {.limbs = {0, 0, 0, 1}};

    Uint320 expected_result = {.limbs = {1, 0, 0, 0, 0}};

    uint320_uint256_addition(&a, &b, &result);

    ASSERT_UINT320_EQUAL(expected_result, result);
}

void test_uint320_uint256_addition_big_320_bits_plus_big_256_bits(void)
{
    Uint320 result;

    Uint320 a = {.limbs = {0x116f4fb09f8f8999, 0xe219e8541ac086b1, 0x09aaef796cb60f6b, 0xbbddb229d724b409, 0x94ba266e9f1d0639}};
    Uint256 b = {.limbs = {0xec06b506059a5650, 0x22b1f690232854ef, 0xd6c21268f3dcbb22, 0x8d1f0333f78f1983}};

    Uint320 expected_result = {.limbs = {0x116f4fb09f8f899a, 0xce209d5a205add01, 0x2c5ce6098fde645b, 0x929fc492cb016f2c, 0x21d929a296ac1fbc}};

    uint320_uint256_addition(&a, &b, &result);

    ASSERT_UINT320_EQUAL(expected_result, result);
}

void test_uint320_uint256_addition_big_320_0_1_pattern_plus_0_1_pattern(void)
{
    Uint320 result;

    Uint320 a = {.limbs = {
                     0b0101010101010101010101010101010101010101010101010101010101010101,
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

    Uint320 expected_result = {.limbs = {0x5555555555555555, 0xaaaaaaaaaaaaaaaa, 0xaaaaaaaaaaaaaaaa, 0xaaaaaaaaaaaaaaaa, 0xaaaaaaaaaaaaaaaa}};

    uint320_uint256_addition(&a, &b, &result);

    ASSERT_UINT320_EQUAL(expected_result, result);
}

void test_uint320_uint256_addition_big_320_1_0_pattern_plus_0_1_pattern(void)
{
    Uint320 result;

    Uint320 a = {.limbs = {
                     0b1010101010101010101010101010101010101010101010101010101010101010,
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

    Uint320 expected_result = {.limbs = {0xaaaaaaaaaaaaaaaa, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff}};

    uint320_uint256_addition(&a, &b, &result);

    ASSERT_UINT320_EQUAL(expected_result, result);
}

void test_uint320_uint256_addition_big_320_1_0_pattern_plus_1_0_pattern(void)
{
    Uint320 result;

    Uint320 a = {.limbs = {
                     0b1010101010101010101010101010101010101010101010101010101010101010,
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

    Uint320 expected_result = {.limbs = {0xaaaaaaaaaaaaaaab,0x5555555555555555,0x5555555555555555,0x5555555555555555,0x5555555555555554}};

    uint320_uint256_addition(&a, &b, &result);

    ASSERT_UINT320_EQUAL(expected_result, result);
}
