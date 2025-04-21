#include "unity/unity.h"
#include "montgomery/montgomery_inverse.h"

void test_montgomery_inverse_n_minus_1(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {
                     0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xfffffffdfffff85e}};

    Uint256 expected_result = {.limbs = {
                                   0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xfffffffdfffff85e}};

    montgomery_inverse(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_montgomery_inverse_n_minus_2(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {
                     0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xfffffffcfffff48d

                 }};

    Uint256 expected_result = {.limbs = {
                                   0x7fffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xfffffffefffffc2f

                               }};

    montgomery_inverse(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_montgomery_inverse_random_number_1(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {

                     0x5109b8460a788d53, 0x7afd6df1d25255dd, 0x87728ee10d7a4ceb, 0x847afdcedac29c2f}};

    Uint256 expected_result = {.limbs = {
                                   0x8fad69f2280696c1, 0x9e131abd9c5e0d97, 0xb1c0a683db3a413c, 0x8f5dab178956d9be}};

    montgomery_inverse(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_montgomery_inverse_random_number_2(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {

                     0x6844c0817bff0b91, 0x465e0a17f6b8c7cf, 0xca269d13b7691888, 0xb2b4560bc9185cce

                 }};

    Uint256 expected_result = {.limbs = {
                                   0xdb8a4399d8003515, 0xace1c03ce5df9755, 0xc059539df314d96a, 0xe94a1a7ec3486c71

                               }};

    montgomery_inverse(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_montgomery_inverse_random_number_3(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {

                     0xbb2c7d0c59cf7401, 0x883fde391b66676b, 0x8017e5b4e56001f6, 0x678634a4c98d871e

                 }};

    Uint256 expected_result = {.limbs = {
                                   0xdb1a049702f2aa1b, 0x8b19a5590f0efeba, 0x376879942695ef77, 0x41ca9f9c4e9531ff

                               }};

    montgomery_inverse(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_montgomery_inverse_random_number_4(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {

                     0x8228b27573f09d7a, 0x4fdf6c5a629c2a1f, 0x72d0dfddb1469d6a, 0xe38c07a6030493f2

                 }};

    Uint256 expected_result = {.limbs = {
                                   0xcbf3a853d143bde3, 0x7807aba66c16e018, 0x84eb186329f5dc1a, 0xb1161888f56cd916

                               }};

    montgomery_inverse(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}