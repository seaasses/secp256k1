#include "structs/uint256.h"
#include "unity/unity.h"
#include <stdio.h>

void assert_uint512_equal(Uint512 expected, Uint512 actual)
{

    char message[1000];
    for (int i = 7; i >= 0; --i)
    {
        sprintf(message, "Expected %llu %llu %llu %llu %llu %llu %llu %llu Was %llu %llu %llu %llu %llu %llu %llu %llu",
                expected.limbs[0], expected.limbs[1], expected.limbs[2], expected.limbs[3],
                expected.limbs[4], expected.limbs[5], expected.limbs[6], expected.limbs[7],
                actual.limbs[0], actual.limbs[1], actual.limbs[2], actual.limbs[3],
                actual.limbs[4], actual.limbs[5], actual.limbs[6], actual.limbs[7]
            
            );
        TEST_ASSERT_EQUAL_UINT64_MESSAGE(expected.limbs[i], actual.limbs[i], message);
    }
}

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