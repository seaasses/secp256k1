#include "unity/unity.h"
#include "montgomery/from_montgomery.h"

// same tests used on from montgomery

void test_from_montgomery_final_0(void)
{
    Uint256 result;

    Uint256 expected_result = {.limbs = {
                     0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000

                 }};
    Uint256 a = {.limbs = {
                                   0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000

                               }};

    from_montgomery(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_from_montgomery_final_1(void)
{
    Uint256 result;

    Uint256 expected_result = {.limbs = {
                     0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000001

                 }};
    Uint256 a = {.limbs = {
                                   0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x00000001000003d1

                               }};

    from_montgomery(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_from_montgomery_final_n_minus_1(void)
{
    Uint256 result;

    Uint256 expected_result = {.limbs = {
                     0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xfffffffefffffc2e

                 }};
    Uint256 a = {.limbs = {
                                   0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xfffffffdfffff85e

                               }};

    from_montgomery(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_from_montgomery_final_r_mod_n(void)
{
    Uint256 result;

    Uint256 expected_result = {.limbs = {
                     0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x00000001000003d1

                 }};
    Uint256 a = {.limbs = {
                                   0x0000000000000000, 0x0000000000000000, 0x0000000000000001, 0x000007a2000e90a1

                               }};

    from_montgomery(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_from_montgomery_final_random_number(void)
{
    Uint256 result;

    Uint256 expected_result = {.limbs = {

                     0x4e5787fcdda0fd5b, 0xf028dc49cd7f12b6, 0xb3f3ca0c53bfe656, 0xddfac4ec6b5db17e}};
    Uint256 a = {.limbs = {
                                   0xd9aef965c38fc829, 0x596fc85ff5ea3551, 0x1925ff627d58d671, 0xe3bec615bca4cfb5

                               }};

    from_montgomery(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}