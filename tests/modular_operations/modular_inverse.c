#include "structs/big_uint.h"
#include "unity/unity.h"
#include "constants/secp256k1.h"
#include "modular_operations/modular_inverse.h"

void test_modular_inverse_1(void)
{
    Uint256 result;

    Uint256 a = {.limbs = {0, 0, 0, 1}};

    Uint256 expected_result = {.limbs = {0, 0, 0, 1}};

    modular_inverse(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_modular_inverse_p_minus_1(void)
{
    Uint256 result;

    Uint256 a = SECP256K1_P_MINUS_1;

    Uint256 expected_result = {.limbs = {0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xfffffffefffffc2e}};

    modular_inverse(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_modular_inverse_12345678910111213141516171819202122232425262728303132333435363738394041424344(void)
{
    Uint256 result;

    Uint256 a = {
        .limbs = {
            0x1b4b68197a5be8d0, 0xed0105423a1de96c, 0xc72933d8691ea68b, 0x97804e5c090e99d8}};

    Uint256 expected_result = {.limbs = {0x96e6fe21dbb12d96, 0xe0cb6c639731c64f, 0x7d6217a9e8e90af0, 0xf85e64682ab85f99}};

    modular_inverse(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_modular_inverse_max_64_bits(void)
{
    Uint256 result;

    Uint256 a = {
        .limbs = {0, 0, 0, 0xFFFFFFFFFFFFFFFF}};

    Uint256 expected_result = {.limbs = {0x6d34ef80a62ee586, 0x6d34ef80a62ee586, 0x6d34ef80a62ee586, 0x6d34ef8038f9f465}};

    modular_inverse(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_modular_inverse_max_128_bits(void)
{
    Uint256 result;

    Uint256 a = {
        .limbs = {0, 0, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF}};

    Uint256 expected_result = {.limbs = {0x3acc5880d4ee94d4, 0x326896ffd14050b2, 0x3acc5880d4ee94d4, 0x326896ff9673f751}};

    modular_inverse(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}

void test_modular_inverse_max_192_bits(void)
{
    Uint256 result;

    Uint256 a = {
        .limbs = {0, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF}};

    Uint256 expected_result = {.limbs = {0x6bf673e6dc694430, 0xe3f9984011b6d6d6, 0x1d44e359b80eca7f, 0x6bf673e67072ceae}};

    modular_inverse(&a, &result);

    ASSERT_UINT256_EQUAL(expected_result, result);
}
