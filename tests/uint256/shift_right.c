#include "structs/uint256.h"
#include "unity/unity.h"
#include "uint256/shift_right.h"

void test_shift_right_0(void)
{
    Uint256 x = (Uint256){.limbs = {0, 0, 0, 0}};

    Uint256 expected_result = (Uint256){.limbs = {0, 0, 0, 0}};

    Uint256 result;

    uint256_shift_right(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_shift_right_1(void)
{
    Uint256 x = (Uint256){.limbs = {0, 0, 0, 1}};

    Uint256 expected_result = (Uint256){.limbs = {0, 0, 0, 0}};

    Uint256 result;

    uint256_shift_right(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_shift_right_between_limbs_0_1(void)
{
    Uint256 x = (Uint256){.limbs = {1, 0, 0, 0}};

    Uint256 expected_result = (Uint256){
        .limbs = {
            0, 0x8000000000000000, 0, 0}};
    Uint256 result;

    uint256_shift_right(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_shift_right_between_limbs_1_2(void)
{
    Uint256 x = (Uint256){.limbs = {
                              0x0000000000000000,
                              0x0000000000000001,
                              0x0000000000000000,
                              0x0000000000000000,
                          }};

    Uint256 expected_result = (Uint256){
        .limbs = {
            0x0000000000000000,
            0x0000000000000000,
            0x8000000000000000,
            0x0000000000000000,
        }};

    Uint256 result;

    uint256_shift_right(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_shift_right_between_limbs_2_3(void)
{
    Uint256 x = (Uint256){.limbs = {
                              0x0000000000000000,
                              0x0000000000000000,
                              0x0000000000000001,
                              0x0000000000000000,
                          }};

    Uint256 expected_result = (Uint256){
        .limbs = {
            0x0000000000000000,
            0x0000000000000000,
            0x0000000000000000,
            0x8000000000000000,
        }};

    Uint256 result;

    uint256_shift_right(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_shift_right_lose_least_significant_bit(void)
{
    Uint256 x = (Uint256){.limbs = {
                              0, 0, 0, 1}};

    Uint256 expected_result = (Uint256){
        .limbs = {
            0, 0, 0, 0}};

    Uint256 result;

    uint256_shift_right(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_shift_right_all_1s(void)
{
    Uint256 x = (Uint256){.limbs = {
                              0xFFFFFFFFFFFFFFFF,
                              0xFFFFFFFFFFFFFFFF,
                              0xFFFFFFFFFFFFFFFF,
                              0xFFFFFFFFFFFFFFFF,

                          }};

    Uint256 expected_result = (Uint256){
        .limbs = {

            0xFFFFFFFFFFFFFFFF >> 1,
            0xFFFFFFFFFFFFFFFF,
            0xFFFFFFFFFFFFFFFF,
            0xFFFFFFFFFFFFFFFF}};

    Uint256 result;

    uint256_shift_right(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_shift_right_0_1_bits_pattern(void)
{
    Uint256 x = (Uint256){.limbs = {
                              0b0101010101010101010101010101010101010101010101010101010101010101,
                              0b0101010101010101010101010101010101010101010101010101010101010101,
                              0b0101010101010101010101010101010101010101010101010101010101010101,
                              0b0101010101010101010101010101010101010101010101010101010101010101,

                          }};

    Uint256 expected_result = (Uint256){
        .limbs = {
            0b0010101010101010101010101010101010101010101010101010101010101010,
            0b1010101010101010101010101010101010101010101010101010101010101010,
            0b1010101010101010101010101010101010101010101010101010101010101010,
            0b1010101010101010101010101010101010101010101010101010101010101010,

        }};

    Uint256 result;

    uint256_shift_right(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_shift_right_1_0_bits_pattern(void)
{
    Uint256 x = (Uint256){.limbs = {
                              0b1010101010101010101010101010101010101010101010101010101010101010,
                              0b1010101010101010101010101010101010101010101010101010101010101010,
                              0b1010101010101010101010101010101010101010101010101010101010101010,
                              0b1010101010101010101010101010101010101010101010101010101010101010,

                          }};

    Uint256 expected_result = (Uint256){
        .limbs = {

            0b0101010101010101010101010101010101010101010101010101010101010101,
            0b0101010101010101010101010101010101010101010101010101010101010101,
            0b0101010101010101010101010101010101010101010101010101010101010101,
            0b0101010101010101010101010101010101010101010101010101010101010101,

        }};

    Uint256 result;

    uint256_shift_right(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_shift_right_0_ff_bytes_pattern(void)
{
    Uint256 x = (Uint256){.limbs = {
                              0x00FF00FF00FF00FF,
                              0x00FF00FF00FF00FF,
                              0x00FF00FF00FF00FF,
                              0x00FF00FF00FF00FF,
                          }};

    Uint256 expected_result = (Uint256){
        .limbs = {

            0b0000000001111111100000000111111110000000011111111000000001111111,
            0b1000000001111111100000000111111110000000011111111000000001111111,
            0b1000000001111111100000000111111110000000011111111000000001111111,
            0b1000000001111111100000000111111110000000011111111000000001111111,
        }};

    Uint256 result;

    uint256_shift_right(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_shift_right_ff_00_bytes_pattern(void)
{
    Uint256 x = (Uint256){.limbs = {
                              0xFF00FF00FF00FF00,
                              0xFF00FF00FF00FF00,
                              0xFF00FF00FF00FF00,
                              0xFF00FF00FF00FF00,
                          }};

    Uint256 expected_result = (Uint256){
        .limbs = {
            0b0111111110000000011111111000000001111111100000000111111110000000,
            0b0111111110000000011111111000000001111111100000000111111110000000,
            0b0111111110000000011111111000000001111111100000000111111110000000,
            0b0111111110000000011111111000000001111111100000000111111110000000,
        }};

    Uint256 result;

    uint256_shift_right(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_shift_right_ffffffffffffffff_0000000000000000_limbs_pattern(void)
{
    Uint256 x = (Uint256){.limbs = {
                              0xFFFFFFFFFFFFFFFF,
                              0x0000000000000000,
                              0xFFFFFFFFFFFFFFFF,
                              0x0000000000000000,
                          }};

    Uint256 expected_result = (Uint256){
        .limbs = {
            0b0111111111111111111111111111111111111111111111111111111111111111,
            0b1000000000000000000000000000000000000000000000000000000000000000,
            0b0111111111111111111111111111111111111111111111111111111111111111,
            0b1000000000000000000000000000000000000000000000000000000000000000,
        }};

    Uint256 result;

    uint256_shift_right(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_shift_right_0000000000000000_ffffffffffffffff_limbs_pattern(void)
{
    Uint256 x = (Uint256){.limbs = {
                              0x0000000000000000,
                              0xFFFFFFFFFFFFFFFF,
                              0x0000000000000000,
                              0xFFFFFFFFFFFFFFFF,
                          }};

    Uint256 expected_result = (Uint256){
        .limbs = {
            0b0000000000000000000000000000000000000000000000000000000000000000,
            0b0111111111111111111111111111111111111111111111111111111111111111,
            0b1000000000000000000000000000000000000000000000000000000000000000,
            0b0111111111111111111111111111111111111111111111111111111111111111,
        }};

    Uint256 result;

    uint256_shift_right(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_shift_right_bit_inside_byte(void)
{
    Uint256 x = (Uint256){.limbs = {
                              0b0010000000010000010000000000100000001000000100000101000000001000,
                              0b0000001000000000010000000100010000010000000100000100000000000010,
                              0b1000000000101000000110000100000000000100000000000010000000010000,
                              0b0000001000100000010010000100000000000010000000000100010000001000,
                          }};

    Uint256 expected_result = (Uint256){
        .limbs = {
            0b0001000000001000001000000000010000000100000010000010100000000100,
            0b0000000100000000001000000010001000001000000010000010000000000001,
            0b0100000000010100000011000010000000000010000000000001000000001000,
            0b0000000100010000001001000010000000000001000000000010001000000100,
        }};

    Uint256 result;

    uint256_shift_right(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_shift_right_big_number(void)
{
    Uint256 x = (Uint256){.limbs = {
                              0xd5a49ba60446902d,
                              0x3b97e1755ee57b3b,
                              0x80bcb60beb05a7f8,
                              0x9fdf96ddcfa9852d,
                          }};

    Uint256 expected_result = (Uint256){
        .limbs = {
            0x6ad24dd302234816,
            0x9dcbf0baaf72bd9d,
            0xc05e5b05f582d3fc,
            0x4fefcb6ee7d4c296,
        }};

    Uint256 result;

    uint256_shift_right(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}
