#include "structs/point.h"
#include "structs/big_uint.h"
#include "unity/unity.h"
#include "secp256k1/g_times_scalar.h"
#include "constants/secp256k1.h"

void test_generator_point_times_1(void)
{
    Point result_point;

    Uint256 scalar = {
        .limbs = {0, 0, 0, 1}};

    Point expected_point = SECP256K1_G;

    g_times_scalar(&scalar, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}

void test_generator_point_times_big_number_0(void)
{
    Point result_point;

    Uint256 scalar = SECP256K1_P_MINUS_1;

    Point expected_point = {
        .x = {
            .limbs = {
                0x02541d1403fc71a5, 0xd927923b20a673e7, 0x69284b16e7d1f597, 0xf9413dc64e82fc48

            }},
        .y = {.limbs = {

                  0x621239e38c2af6bc, 0x145db2424cf44bb8, 0xed12351858f67c7c, 0x6130a2f69fe4a28c

              }}};

    g_times_scalar(&scalar, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}

void test_generator_point_times_big_number_1(void)
{
    Point result_point;

    Uint256 scalar = {
        .limbs = {

            0x6d914012b8952160, 0xa79d2f7573143c10, 0xfbf324b497bf9289, 0x2581e55b7f6aabf1

        }};

    Point expected_point = {
        .x = {
            .limbs = {

                0xdf4a2e774212f80b, 0x688835a9eb6836bf, 0x6b7795372c3a1efb, 0x5e26e42bd28dc4ba

            }},
        .y = {.limbs = {

                  0x2cb999fbf85dd51d, 0x4561e142a7b9bd5d, 0xf30b0bc986e37407, 0x48ba9374f6a51d1a

              }}};

    g_times_scalar(&scalar, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}

void test_generator_point_times_big_number_2(void)
{
    Point result_point;

    Uint256 scalar = {
        .limbs = {
            0xfde5e382aa2ef05d, 0xb142e7acfb9cd795, 0xd4756d96d3aeccb8, 0x4c8e74c94999ad0f}};

    Point expected_point = {
        .x = {
            .limbs = {
                0x8b4ab5b746742718, 0x8eecdaa0f5e5e643, 0x10d08ee9ea07529d, 0x1638dae7c82176c3

            }},
        .y = {.limbs = {

                  0x6f4310e4f9218059, 0x0e195da5df3215e8, 0x64f245d87a784209, 0x29e440e9f2f61c98

              }}};

    g_times_scalar(&scalar, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}