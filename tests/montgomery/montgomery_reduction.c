#include "unity/unity.h"
#include "montgomery/montgomery_reduction.h"

void test_montgomery_reduction_final_n_minus_1(void)
{
    Uint256 result;

    Uint512 x = {.limbs = {
                     0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xfffffffdfffff85e}};

    Uint256 expected_result = {.limbs = {
                                   0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xfffffffefffffc2e}};

    montgomery_reduction(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_montgomery_reduction_before_mod_n_final_n_minus_1(void)
{
    Uint256 result;

    Uint512 x = {.limbs = {
                     0x000d2af7b79d76d5, 0x6d375ad83db01de8, 0x8e1bfa9802c4b540, 0x9b71e51a5e291a45, 0x16218dc6d2d620a1, 0xf20e2ed404c1e0e1, 0xa473ec9cd3d65f54, 0x641e612072e1be62}};

    Uint256 expected_result = {.limbs = {
                                   0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xfffffffefffffc2e}};

    montgomery_reduction(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_montgomery_reduction_before_mod_n_final_1(void)
{
    Uint256 result;

    Uint512 x = {.limbs = {
                     0x0524c8c3b9826bc0, 0xb9cd403e0e6c8c17, 0x078937119f1b9ed9, 0x629b651a59117c64, 0xa51b61484b75853c, 0xd9414713ec34250a, 0x9e3936e664fb5f44, 0x4ebce12372e1c9d5}};

    Uint256 expected_result = {.limbs = {
                                   0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000001}};

    montgomery_reduction(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_montgomery_reduction_1_in_montgomery(void)
{
    Uint256 result;

    Uint512 x = {.limbs = {
                     0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000001}};

    Uint256 expected_result = {.limbs = {
                                   0xc9bd190515538399, 0x9c46c2c295f2b761, 0xbcb223fedc24a059, 0xd838091d0868192a}};

    montgomery_reduction(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}
