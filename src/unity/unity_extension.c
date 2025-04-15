#include "structs/uint256.h"
#include "unity/unity.h"

void assert_uint256_equal(Uint256 expected, Uint256 actual)
{
    TEST_ASSERT_EQUAL_UINT64_ARRAY(expected.limbs, actual.limbs, 4);
}