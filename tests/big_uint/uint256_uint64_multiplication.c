#include "structs/big_uint.h"
#include "unity/unity.h"
#include "big_uint/uint256_uint64_multiplication.h"

void test_uint256_uint64_2_times_3(void)
{
    Uint320 result;

    Uint256 a = {.limbs = {0, 0, 0, 2}};

    unsigned long long b = 3;

    Uint320 expected = {
        .limbs = {
            0, 0, 0, 0, 6}};

    uint256_uint64_multiplication(&a, b, &result);

    ASSERT_UINT320_EQUAL(expected, result);
}

void test_uint256_uint64_0x8000000000000000_times_two(void)
{
    Uint320 result;

    Uint256 a = {.limbs = {0, 0, 0, 0x8000000000000000}};

    unsigned long long b = 2;

    Uint320 expected = {
        .limbs = {
            0, 0, 0, 1, 0}};

    uint256_uint64_multiplication(&a, b, &result);

    ASSERT_UINT320_EQUAL(expected, result);
}

void test_uint256_uint64_max_64_bits_times_two(void)
{
    Uint320 result;

    Uint256 a = {.limbs = {0, 0, 0, 0xFFFFFFFFFFFFFFFF}};

    unsigned long long b = 2;

    Uint320 expected = {
        .limbs = {
            0, 0, 0, 1, 0xFFFFFFFFFFFFFFFE}};

    uint256_uint64_multiplication(&a, b, &result);

    ASSERT_UINT320_EQUAL(expected, result);
}

void test_uint256_uint64_max_128_bits_times_two(void)
{
    Uint320 result;

    Uint256 a = {.limbs = {0, 0, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF}};

    unsigned long long b = 2;

    Uint320 expected = {
        .limbs = {
            0, 0, 1, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFE}};

    uint256_uint64_multiplication(&a, b, &result);

    ASSERT_UINT320_EQUAL(expected, result);
}

void test_uint256_uint64_max_192_bits_times_two(void)
{
    Uint320 result;

    Uint256 a = {.limbs = {0, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF}};

    unsigned long long b = 2;

    Uint320 expected = {
        .limbs = {
            0, 1, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFE}};

    uint256_uint64_multiplication(&a, b, &result);

    ASSERT_UINT320_EQUAL(expected, result);
}

void test_uint256_uint64_max_256_bits_times_two(void)
{
    Uint320 result;

    Uint256 a = {.limbs = {0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF}};

    unsigned long long b = 2;

    Uint320 expected = {
        .limbs = {
            1, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFE}};

    uint256_uint64_multiplication(&a, b, &result);

    ASSERT_UINT320_EQUAL(expected, result);
}

void test_uint256_uint64_max_256_bits_times_max_64_bits(void)
{
    Uint320 result;

    Uint256 a = {.limbs = {0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF}};

    unsigned long long b = 0xFFFFFFFFFFFFFFFF;

    Uint320 expected = {
        .limbs = {
            0xfffffffffffffffe, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0x0000000000000001}};

    uint256_uint64_multiplication(&a, b, &result);

    ASSERT_UINT320_EQUAL(expected, result);
}

void test_uint256_uint64_big_256_bits_times_big_64_bits(void)
{
    Uint320 result;

    Uint256 a = {.limbs = {
                     0x508fec357abc600c, 0xf3716d84a8755d89, 0xb5d1aeee4f25af70, 0x35d57d12ac76d020}};

    unsigned long long b = 0xef7e162b9b20f65d;

    Uint320 expected = {
        .limbs = {
            0x4b5e0b5647330f74, 0xa4cf8f3dd7c6b9fa, 0x6e4d2ca63141ff09, 0x56e02de137b4f8a6, 0x231795c037285ba0}};

    uint256_uint64_multiplication(&a, b, &result);

    ASSERT_UINT320_EQUAL(expected, result);
}

void test_uint256_uint64_big_256_bits_times_0(void)
{
    Uint320 result;

    Uint256 a = {.limbs = {
                     0xd2c4fd78ff1f6b2f, 0x95ea8418bbfd2c9f, 0x69ffcaaf952507ea, 0xf7e67b850acb15f1}};

    unsigned long long b = 0;

    Uint320 expected = {
        .limbs = {0, 0, 0, 0, 0}};

    uint256_uint64_multiplication(&a, b, &result);

    ASSERT_UINT320_EQUAL(expected, result);
}
