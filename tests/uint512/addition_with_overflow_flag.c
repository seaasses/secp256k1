#include "structs/uint512.h"
#include "unity/unity.h"
#include "uint512/addition_with_overflow_flag.h"

void test_uint512_addition_with_overflow_flag_2_3(void)
{
    Uint512 result;
    unsigned int overflow_flag;

    Uint512 a = {.limbs = {0, 0, 0, 0, 0, 0, 0, 2}};
    Uint512 b = {.limbs = {0, 0, 0, 0, 0, 0, 0, 3}};

    Uint512 expected_result = {.limbs = {0, 0, 0, 0, 0, 0, 0, 5}};

    uint512_addition_with_overflow_flag(&a, &b, &result, &overflow_flag);

    ASSERT_UINT512_EQUAL(expected_result, result);
    TEST_ASSERT_EQUAL_UINT32(0, overflow_flag);
}

void test_uint512_addition_with_overflow_flag_sum_0(void)
{
    Uint512 result;
    unsigned int overflow_flag;

    Uint512 a = {.limbs = {0x079e90a9ab46a86c, 0xd4f5c77a1ccb1854, 0x83e6e3a630fdd9b2, 0x897ea34d128f0f20, 0x21afed62f9913e1e, 0xb258abb0ba855860, 0x0c3cef96ac955bb2, 0xf838a1614e12b7c1}};
    Uint512 b = {.limbs = {0, 0, 0, 0, 0, 0, 0, 0}};

    Uint512 expected_result = {.limbs = {0x079e90a9ab46a86c, 0xd4f5c77a1ccb1854, 0x83e6e3a630fdd9b2, 0x897ea34d128f0f20, 0x21afed62f9913e1e, 0xb258abb0ba855860, 0x0c3cef96ac955bb2, 0xf838a1614e12b7c1}};

    uint512_addition_with_overflow_flag(&a, &b, &result, &overflow_flag);

    ASSERT_UINT512_EQUAL(expected_result, result);
    TEST_ASSERT_EQUAL_UINT32(0, overflow_flag);
}

void test_uint512_addition_with_overflow_flag_all_bits_set_plus_1(void)
{
    Uint512 result;
    unsigned int overflow_flag;

    Uint512 a = {.limbs = {0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF}};
    Uint512 b = {.limbs = {0, 0, 0, 0, 0, 0, 0, 1}};

    Uint512 expected_result = {.limbs = {0, 0, 0, 0, 0, 0, 0, 0}};

    uint512_addition_with_overflow_flag(&a, &b, &result, &overflow_flag);

    ASSERT_UINT512_EQUAL(expected_result, result);
    TEST_ASSERT_EQUAL_UINT32(1, overflow_flag);
}

void test_uint512_addition_with_overflow_flag_all_bits_set_plus_all_bits_set(void)
{
    Uint512 result;
    unsigned int overflow_flag;

    Uint512 a = {.limbs = {0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF}};
    Uint512 b = {.limbs = {0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF}};

    Uint512 expected_result = {.limbs = {0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFE}};

    uint512_addition_with_overflow_flag(&a, &b, &result, &overflow_flag);

    ASSERT_UINT512_EQUAL(expected_result, result);
    TEST_ASSERT_EQUAL_UINT32(1, overflow_flag);
}

void test_uint512_addition_with_overflow_flag_most_significant_bit_set_plus_most_significant_bit_set(void)
{
    Uint512 result;
    unsigned int overflow_flag;

    Uint512 a = {.limbs = {0x8000000000000000, 0, 0, 0, 0, 0, 0, 0}};
    Uint512 b = {.limbs = {0x8000000000000000, 0, 0, 0, 0, 0, 0, 0}};

    Uint512 expected_result = {.limbs = {0, 0, 0, 0, 0, 0, 0, 0}};

    uint512_addition_with_overflow_flag(&a, &b, &result, &overflow_flag);

    ASSERT_UINT512_EQUAL(expected_result, result);
    TEST_ASSERT_EQUAL_UINT32(1, overflow_flag);
}

void test_uint512_addition_with_overflow_flag_without_overflow(void)
{
    Uint512 result;
    unsigned int overflow_flag;

    Uint512 a = {.limbs = {
                     0x2349ca49e70d7e1a, 0x0351d6b078e03edc, 0x9c8c52256296b2d6, 0xd3fb10c157eb884a, 0x4341f68a2e15785d, 0x8b939124678e7944, 0xdc7268d66f9f0855, 0x6218b38fbce08908}};
    Uint512 b = {.limbs = {
                     0x9c4aee9d2549a8e3, 0xef07ddcd06f2d268, 0x2a0f832cb454a08c, 0xf70bd7d2f1b79d5e, 0xa447cf325f73ca4b, 0x4b2da7196b5c4225, 0x8b611638361d5531, 0xe18354a6dc57ac68}};

    Uint512 expected_result = {.limbs = {
                                   0xbf94b8e70c5726fd, 0xf259b47d7fd31144, 0xc69bd55216eb5363, 0xcb06e89449a325a8, 0xe789c5bc8d8942a8, 0xd6c1383dd2eabb6a, 0x67d37f0ea5bc5d87, 0x439c083699383570}};

    uint512_addition_with_overflow_flag(&a, &b, &result, &overflow_flag);

    ASSERT_UINT512_EQUAL(expected_result, result);
    TEST_ASSERT_EQUAL_UINT32(0, overflow_flag);
}

void test_uint512_addition_with_overflow_flag_with_overflow(void)
{
    Uint512 result;
    unsigned int overflow_flag;

    Uint512 a = {.limbs = {
                     0x40910877edbc6f76, 0xdf2e47cd601ad388, 0xf514544a89874e40, 0x9549f1356e5a9c3d, 0xf9a85755de2c160b, 0x7d5585234a9b7efd, 0x03b1ede80c393f63, 0x24c14d2441574e63}};
    Uint512 b = {.limbs = {
                     0xdbc597e745fe5438, 0x00d66d1b4f340542, 0x9cd14c9a949c5742, 0xf0d504e881a13a37, 0x429b61eed83d89da, 0xe4c6bd61445b7251, 0x07c665792f3c0b2a, 0x43c3c83dd419e58f}};

    Uint512 expected_result = {.limbs = {
                                   0x1c56a05f33bac3ae, 0xe004b4e8af4ed8cb, 0x91e5a0e51e23a583, 0x861ef61deffbd675, 0x3c43b944b6699fe6, 0x621c42848ef6f14e, 0x0b7853613b754a8d, 0x68851562157133f2}};

    uint512_addition_with_overflow_flag(&a, &b, &result, &overflow_flag);

    ASSERT_UINT512_EQUAL(expected_result, result);
    TEST_ASSERT_EQUAL_UINT32(1, overflow_flag);
}
