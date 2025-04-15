#include "structs/uint256.h"
#include "unity/unity.h"
#include "uint256/shift_left.h"

void test_shift_left_0(void)
{
    Uint256 x = (Uint256){.limbs = {0, 0, 0, 0}};

    Uint256 expected_result = (Uint256){.limbs = {0, 0, 0, 0}};

    Uint256 result;

    uint256_shift_left(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_shift_left_1(void)
{
    Uint256 x = (Uint256){.limbs = {0, 0, 0, 1}};

    Uint256 expected_result = (Uint256){.limbs = {0, 0, 0, 2}};

    Uint256 result;

    uint256_shift_left(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_shift_left_between_limbs_3_2(void)
{
    Uint256 x = (Uint256){

        .limbs = {0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x8000000000000000}

    };

    Uint256 expected_result = (Uint256){

        .limbs = {0x0000000000000000, 0x0000000000000000, 0x0000000000000001, 0x0000000000000000}};

    Uint256 result;

    uint256_shift_left(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_shift_left_between_limbs_2_1(void)
{
    Uint256 x = (Uint256){
        .limbs = {0x0000000000000000, 0x0000000000000000, 0x8000000000000000, 0x0000000000000000}};

    Uint256 expected_result = (Uint256){
        .limbs = {0x0000000000000000, 0x0000000000000001, 0x0000000000000000, 0x0000000000000000}};

    Uint256 result;

    uint256_shift_left(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_shift_left_between_limbs_1_0(void)
{
    Uint256 x = (Uint256){
        .limbs = {0x0000000000000000, 0x8000000000000000, 0x0000000000000000, 0x0000000000000000}};

    Uint256 expected_result = (Uint256){
        .limbs = {
            0x0000000000000001,
            0x0000000000000000,
            0x0000000000000000,
            0x0000000000000000,
        }};

    Uint256 result;

    uint256_shift_left(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_shift_left_lose_more_significant_bit(void)
{
    Uint256 x = (Uint256){
        .limbs = {

            0x8000000000000000,
            0x0000000000000000,
            0x0000000000000000,
            0x0000000000000000,

        }};

    Uint256 expected_result = (Uint256){
        .limbs = {
            0, 0, 0, 0}};

    Uint256 result;

    uint256_shift_left(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_shift_left_all_1s(void)
{
    Uint256 x = (Uint256){
        .limbs = {
            0xFFFFFFFFFFFFFFFF,
            0xFFFFFFFFFFFFFFFF,
            0xFFFFFFFFFFFFFFFF,
            0xFFFFFFFFFFFFFFFF,
        }};

    Uint256 expected_result = (Uint256){
        .limbs = {
            0xFFFFFFFFFFFFFFFF,
            0xFFFFFFFFFFFFFFFF,
            0xFFFFFFFFFFFFFFFF,
            0xFFFFFFFFFFFFFFFE,

        }};

    Uint256 result;

    uint256_shift_left(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_shift_left_0_1_bits_pattern(void)
{
    Uint256 x = (Uint256){
        .limbs = {
            0b0101010101010101010101010101010101010101010101010101010101010101,
            0b0101010101010101010101010101010101010101010101010101010101010101,
            0b0101010101010101010101010101010101010101010101010101010101010101,
            0b0101010101010101010101010101010101010101010101010101010101010101,
        }};

    Uint256 expected_result = (Uint256){
        .limbs = {
            0b1010101010101010101010101010101010101010101010101010101010101010,
            0b1010101010101010101010101010101010101010101010101010101010101010,
            0b1010101010101010101010101010101010101010101010101010101010101010,
            0b1010101010101010101010101010101010101010101010101010101010101010,

        }};

    Uint256 result;

    uint256_shift_left(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_shift_left_1_0_bits_pattern(void)
{
    Uint256 x = (Uint256){
        .limbs = {
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
            0b0101010101010101010101010101010101010101010101010101010101010100,
        }};

    Uint256 result;

    uint256_shift_left(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_shift_left_0_ff_bytes_pattern(void)
{
    Uint256 x = (Uint256){
        .limbs = {
            0x00FF00FF00FF00FF,
            0x00FF00FF00FF00FF,
            0x00FF00FF00FF00FF,
            0x00FF00FF00FF00FF,
        }};

    Uint256 expected_result = (Uint256){
        .limbs = {
            0x01FE01FE01FE01FE,
            0x01FE01FE01FE01FE,
            0x01FE01FE01FE01FE,
            0x01FE01FE01FE01FE,
        }};

    Uint256 result;

    uint256_shift_left(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_shift_left_ff_00_bytes_pattern(void)
{
    Uint256 x = (Uint256){
        .limbs = {
            0xFF00FF00FF00FF00,
            0xFF00FF00FF00FF00,
            0xFF00FF00FF00FF00,
            0xFF00FF00FF00FF00,
        }};

    Uint256 expected_result = (Uint256){
        .limbs = {
            0xFE01FE01FE01FE01,
            0xFE01FE01FE01FE01,
            0xFE01FE01FE01FE01,
            0xFE01FE01FE01FE00,
        }};

    Uint256 result;

    uint256_shift_left(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_shift_left_ffffffffffffffff_0000000000000000_limbs_pattern(void)
{
    Uint256 x = (Uint256){
        .limbs = {
            0xFFFFFFFFFFFFFFFF,
            0x0000000000000000,
            0xFFFFFFFFFFFFFFFF,
            0x0000000000000000,
        }};

    Uint256 expected_result = (Uint256){
        .limbs = {
            0xFFFFFFFFFFFFFFFE,
            0x0000000000000001,
            0xFFFFFFFFFFFFFFFE,
            0x0000000000000000,
        }};

    Uint256 result;

    uint256_shift_left(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_shift_left_0000000000000000_ffffffffffffffff_limbs_pattern(void)
{
    Uint256 x = (Uint256){
        .limbs = {
            0x0000000000000000,
            0xFFFFFFFFFFFFFFFF,
            0x0000000000000000,
            0xFFFFFFFFFFFFFFFF,
        }};

    Uint256 expected_result = (Uint256){
        .limbs = {
            0x0000000000000001,
            0xFFFFFFFFFFFFFFFE,
            0x0000000000000001,
            0xFFFFFFFFFFFFFFFE,
        }};

    Uint256 result;

    uint256_shift_left(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_shift_left_bit_inside_byte(void)
{
    Uint256 x = (Uint256){
        .limbs = {
            0b0010000000010000010000000000100000001000000100000101000000001000,
            0b0000001000000000010000000100010000010000000100000100000000000010,
            0b0000000100101000000110000100000000000100000000000010000000010000,
            0b0000001000100000010010000100000000000001000000000100010000001000,
        }};

    Uint256 expected_result = (Uint256){
        .limbs = {
            0b0100000000100000100000000001000000010000001000001010000000010000,
            0b0000010000000000100000001000100000100000001000001000000000000100,
            0b0000001001010000001100001000000000001000000000000100000000100000,
            0b0000010001000000100100001000000000000010000000001000100000010000,
        }};

    Uint256 result;

    uint256_shift_left(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_shift_left_big_number(void)
{
    Uint256 x = (Uint256){
        .limbs = {
            0xd5a49ba60446902d,
            0x3b97e1755ee57b3b,
            0x80bcb60beb05a7f8,
            0x9fdf96ddcfa9852d,
        }};

    Uint256 expected_result = (Uint256){
        .limbs = {
            0xab49374c088d205a,
            0x772fc2eabdcaf677,
            0x01796c17d60b4ff1,
            0x3fbf2dbb9f530a5a,
        }};

    Uint256 result;

    uint256_shift_left(&x, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}
