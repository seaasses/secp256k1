#include "unity/unity.h"
#include "uint256/multiplication.h"

void test_multiplication_big_number_times_0(void)
{
    Uint512 result;

    Uint256 a = {.limbs = {0xa8bdd892503643b5, 0x4cb58c57708bd434, 0xe02407c491579b2e, 0xa5c02ec76f8acf06}};
    Uint256 b = {.limbs = {0, 0, 0, 0}};

    Uint512 expected_result = {.limbs = {0, 0, 0, 0, 0, 0, 0, 0}};

    uint256_multiplication(&a, &b, &result);

    ASSERT_UINT512_EQUAL(expected_result, result);
}

void test_multiplication_big_number_times_1(void)
{
    Uint512 result;

    Uint256 a = {.limbs = {0xa8bdd892503643b5, 0x4cb58c57708bd434, 0xe02407c491579b2e, 0xa5c02ec76f8acf06}};
    Uint256 b = {.limbs = {0, 0, 0, 1}};

    Uint512 expected_result = {.limbs = {0, 0, 0, 0, 0xa8bdd892503643b5, 0x4cb58c57708bd434, 0xe02407c491579b2e, 0xa5c02ec76f8acf06}};

    uint256_multiplication(&a, &b, &result);

    ASSERT_UINT512_EQUAL(expected_result, result);
}

void test_multiplication_2_3(void)
{
    Uint512 result;

    Uint256 a = {.limbs = {0, 0, 0, 3}};
    Uint256 b = {.limbs = {0, 0, 0, 4}};

    Uint512 expected_result = {.limbs = {0, 0, 0, 0, 0, 0, 0, 12}};

    uint256_multiplication(&a, &b, &result);

    ASSERT_UINT512_EQUAL(expected_result, result);
}

void test_multiplication_least_significant_limb_simple_overflow(void)
{
    Uint512 result;

    Uint256 a = {.limbs = {0, 0, 0, 0x8000000000000000}};
    Uint256 b = {.limbs = {0, 0, 0, 2}};
    // this is like a shift left by 1

    Uint512 expected_result = {.limbs = {0, 0, 0, 0, 0, 0, 1, 0}};

    uint256_multiplication(&a, &b, &result);

    ASSERT_UINT512_EQUAL(expected_result, result);
}

void test_multiplication_least_significant_limb_max_64_bits_times_max_64_bits(void)
{
    Uint512 result;

    Uint256 a = {.limbs = {0, 0, 0, 0xFFFFFFFFFFFFFFFF}};
    Uint256 b = {.limbs = {0, 0, 0, 0xFFFFFFFFFFFFFFFF}};

    Uint512 expected_result = {.limbs = {
                                   0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0xfffffffffffffffe, 0x0000000000000001}};

    uint256_multiplication(&a, &b, &result);

    ASSERT_UINT512_EQUAL(expected_result, result);
}

void test_multiplication_least_significant_limb_overflow_random_number(void)
{
    Uint512 result;

    Uint256 a = {.limbs = {0, 0, 0, 0x5421365376763587}};
    Uint256 b = {.limbs = {0, 0, 0, 0x3476347639968907}};

    Uint512 expected_result = {.limbs = {0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x113d979597cd797b, 0x32d8fa15ebfab5b1}};

    uint256_multiplication(&a, &b, &result);

    ASSERT_UINT512_EQUAL(expected_result, result);
}

void test_multiplication_limb_2_overflow(void)
{
    Uint512 result;

    Uint256 a = {.limbs = {0, 0, 0x8000000000000000, 0}};
    Uint256 b = {.limbs = {0, 0, 0, 2}};

    Uint512 expected_result = {.limbs = {0, 0, 0, 0, 0, 1, 0, 0}};

    uint256_multiplication(&a, &b, &result);

    ASSERT_UINT512_EQUAL(expected_result, result);
}

void test_multiplication_limb_2_random_2_limbs_numbers_that_carry_to_next_limb(void)
{
    Uint512 result;

    Uint256 a = {.limbs = {

                     0, 0, 0x997535849487778F, 0x2345678974567708

                 }};
    Uint256 b = {.limbs = {
                     0, 0, 0x9098654374874686, 0x7683465348739986}};

    Uint512 expected_result = {.limbs = {
                                   0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x56ad486607e8e751, 0xc5b2704092811f03, 0x1ef7a2535c6286fa, 0x1259b4644afe1630}};

    uint256_multiplication(&a, &b, &result);

    ASSERT_UINT512_EQUAL(expected_result, result);
}

void test_multiplication_2_full_limbs(void)
{
    Uint512 result;

    Uint256 a = {.limbs = {

                     0, 0, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF

                 }};
    Uint256 b = {.limbs = {
                     0, 0, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF}};

    Uint512 expected_result = {.limbs = {
                                   0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0xffffffffffffffff, 0xfffffffffffffffe, 0x0000000000000000, 0x0000000000000001}};

    uint256_multiplication(&a, &b, &result);

    ASSERT_UINT512_EQUAL(expected_result, result);
}

void test_multiplication_2_big_numbers_3_limbs_each(void)
{
    Uint512 result;

    Uint256 a = {.limbs = {
                     0x0000000000000000, 0x6f3daacb898aa583, 0xd01bf4057d42483f, 0xbf95d5af7c97ebaf

                 }};
    Uint256 b = {.limbs = {
                     0x0000000000000000, 0xf563ef17481cc6bd, 0xfc9b066f3834e5c0, 0x0c19956aa42bdfd0}};

    Uint512 expected_result = {.limbs = {
                                   0x0000000000000000, 0x0000000000000000, 0x6aa1713287ac17db, 0x2175c919e971c03f, 0x43ff0db761247d6d, 0x186d758f57f5bf00, 0x7dec60e79cef9d0e, 0xba582e144421ef30}};

    uint256_multiplication(&a, &b, &result);

    ASSERT_UINT512_EQUAL(expected_result, result);
}

void test_multiplication_3_full_limbs(void)
{
    Uint512 result;

    Uint256 a = {.limbs = {

                     0, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF

                 }};
    Uint256 b = {.limbs = {
                     0, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF}};

    Uint512 expected_result = {.limbs = {
                                   0x0000000000000000, 0x0000000000000000, 0xffffffffffffffff, 0xffffffffffffffff, 0xfffffffffffffffe, 0x0000000000000000, 0x0000000000000000, 0x0000000000000001}};

    uint256_multiplication(&a, &b, &result);

    ASSERT_UINT512_EQUAL(expected_result, result);
}

void test_multiplication_4_full_limbs(void)
{
    Uint512 result;

    Uint256 a = {.limbs = {
                     0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff}};
    Uint256 b = {.limbs = {
                     0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff}};

    Uint512 expected_result = {.limbs = {
                                   0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xfffffffffffffffe, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000001}};

    uint256_multiplication(&a, &b, &result);

    ASSERT_UINT512_EQUAL(expected_result, result);
}
