#ifndef UNITY_EXTENSION
#define UNITY_EXTENSION

#include "structs/uint256.h"

#define ASSERT_UINT256_EQUAL(expected, actual)  assert_uint256_equal((expected), (actual))

void assert_uint256_equal(Uint256 expected, Uint256 actual);

#endif
