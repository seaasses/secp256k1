#ifndef UNITY_EXTENSION
#define UNITY_EXTENSION

#include "structs/uint256.h"
#include "structs/uint512.h"
#include "structs/point.h"

#define ASSERT_UINT256_EQUAL(expected, actual) assert_uint256_equal((expected), (actual))

#define ASSERT_UINT512_EQUAL(expected, actual) assert_uint512_equal((expected), (actual))

#define ASSERT_POINT_EQUAL(expected, actual) assert_point_equal((expected), (actual))

#define ASSERT_JACOBIAN_POINT_EQUAL(expected, actual) assert_jacobian_point_equal((expected), (actual))

void assert_uint256_equal(Uint256 expected, Uint256 actual);
void assert_uint512_equal(Uint512 expected, Uint512 actual);
void assert_point_equal(Point expected, Point actual);
void assert_jacobian_point_equal(JacobianPoint expected, JacobianPoint actual);

#endif
