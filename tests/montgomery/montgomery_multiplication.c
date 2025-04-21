#include "unity/unity.h"
#include "montgomery/montgomery_multiplication.h"

void test_montgomery_multiplication_random_numbers_0(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {
                     0xd91a10fb1d379421, 0x7dbd7382a42fa7e8, 0x9ac9034321034d06, 0xeda095df54848d25}};

    Uint256 b = {.limbs = {
                     0x21c77e0971d99dee, 0x901330c1bc24c50e, 0xa98cc18c8578d64d, 0x009a0924b3437eeb}};

    Uint256 expected_result = {.limbs = {
                                   0x156f731a4ef63524, 0x5696d34e8be7d061, 0xb6cd5c1695cfb692, 0xf97ecff92f2875db}};

    montgomery_multiplication(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_montgomery_multiplication_random_numbers_1(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {
                     0x0969b0f599a94ac9, 0x7f3da6ecad6492a2, 0x77f0cc39c201321f, 0xc11992ee01a6f272}};

    Uint256 b = {.limbs = {
                     0x324c0fbff8b01f77, 0x419c9198b92ca8ea, 0x3837e933403bce74, 0x16e3d5e06a7cace5}};

    Uint256 expected_result = {.limbs = {
                                   0xaabb626bb606cac6, 0x18ac1e6101d55e6c, 0x1c6e061f7961ee3d, 0x726f27c859fcea4e}};

    montgomery_multiplication(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_montgomery_multiplication_random_numbers_2(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {
                     0x3fca6ad0971a8daa, 0xe95b711387394447, 0x0874c9313bd5de26, 0xeedfba0290828f2c}};

    Uint256 b = {.limbs = {
                     0x122a54361db1a5fd, 0x47b8868de9c25a1e, 0xe2cf1f6bdf1e0429, 0xb8bcdfedc907f3c1}};

    Uint256 expected_result = {.limbs = {
                                   0x4591798ae7b62aa7, 0x60433ec5701dc5e9, 0x0f4a5493fa95ea39, 0xf75113f8f826067d}};

    montgomery_multiplication(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_montgomery_multiplication_random_numbers_3(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {
                     0xd40c26616dc96198, 0xc0ad413d43c22762, 0x4e7062e71f4c2bb4, 0x04839366c679ee04}};

    Uint256 b = {.limbs = {
                     0x2d4031c8e772e1e5, 0x324299a0d05509f9, 0x708b2501ca247942, 0x785336944967e73b}};

    Uint256 expected_result = {.limbs = {
                                   0x0333e904611de063, 0xdce946583c153285, 0x09baef70da59835d, 0xa97e9b388d383c22}};

    montgomery_multiplication(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_montgomery_multiplication_random_numbers_to_subtract_zero(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {
                     0xaa17c70e2981b7e7, 0xd7d8c7e4cf617bdd, 0x7d71a3b2ba4fc4cf, 0x2addeaa5bae95c41}};

    Uint256 b = {.limbs = {
                     0x7b54021420cdccdb, 0xea2c368bb496767d, 0x51db2c9ebc7c03af, 0xc2b522583627986e}};

    Uint256 expected_result = {.limbs = {
                                   0xf19054046c3bfede, 0x86573ce4d0baa207, 0xb590cedd08beee5f, 0x47c9df7c698f27ee}};

    montgomery_multiplication(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_montgomery_multiplication_random_numbers_5_to_subtract_not_zero(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {
                     0xa76a3a5d5cb384fa, 0x5dec10db490a6db2, 0xe567dae7805b0811, 0x7ec5916a46b3ebe2

                 }};

    Uint256 b = {.limbs = {
                     0x39aad5fae6fd80b4, 0x2271670620ff8614, 0x1e7d2d98bd67e220, 0xa543d1ec3a2f75a6}};

    Uint256 expected_result = {.limbs = {
                                   0x0bcc3c8d3d206a0a, 0x77084ef32c3977a1, 0x2db1b47406cd1fdf, 0x7657635d5739bb39

                               }};

    montgomery_multiplication(&a, &b, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}