#include "structs/uint256.h"
#include "unity/unity.h"
#include <stdio.h>

void assert_uint256_equal(Uint256 expected, Uint256 actual)
{

    char message[100];
    for (int i = 0; i != 4; ++i)
    {
        sprintf(message, "Limb %d error", i);
        TEST_ASSERT_EQUAL_UINT64_MESSAGE(expected.limbs[i], actual.limbs[i], message);
    }
}

void assert_point_equal(Point expected, Point actual)
{
    assert_uint256_equal(expected.x, actual.x);
    assert_uint256_equal(expected.y, actual.y);
}

void assert_jacobian_point_equal(JacobianPoint expected, JacobianPoint actual)
{
    assert_uint256_equal(expected.x, actual.x);
    assert_uint256_equal(expected.y, actual.y);
    assert_uint256_equal(expected.z, actual.z);
}