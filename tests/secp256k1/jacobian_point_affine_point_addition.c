#include "structs/point.h"
#include "unity/unity.h"
#include "constants/secp256k1.h"
#include "secp256k1/jacobian_point_affine_point_addition.h"



void test_jacobian_point_affine_point_addition_0(void)
{
    JacobianPoint result_point;

    JacobianPoint point_a = {
        .x = {.limbs = {
        0x8a06975fe1e8573e,0x4b9cc4973eedf5da,0x2e26d4fecb8e5aac,0x4b1f1d2cfb7992a3

              }},
        .y = {.limbs = {

0x083e03193384122a,0x9722893ba8b06d2d,0xa0031adf59dc392c,0x7763c1f7cd8773e5

              }},
        .z = {.limbs = {

0xcf69ed40987b7ab4,0x0cc69cf344f99c45,0xe4360f36b52e0a10,0x60d9194904049630

              }}};

    Point point_b = {
        .x = {.limbs = {
        0x893b8ba24727ab64,0xdd29679a4a18095f,0xf508b53aec921755,0xf35b4a2aef3ef5f2

              }},
        .y = {.limbs = {

0x8bb1e2ab22ae07cc,0x2cc7a234d8e9cba7,0xf4a6728f829898af,0x5e3d1c56270ccbb5

              }},
    };

    JacobianPoint expected_jacobian_point = {
        .x = {.limbs = {
0xfebdd241fecbaf16,0x7871e5f85aeb07f0,0x2403c9cbde400983,0xa591e3ca4bbfd80b

              }},
        .y = {.limbs = {

0x8f907d7bc5203f50,0x94b277146e551dfa,0x6a7b95698525a378,0x3ae83f6471733c22

              }},

        .z = {.limbs = {

0x7f5821a64664d3bd,0x57ec14c66b7ee660,0xefdaffafa06e6fa1,0xb1374d6a93bb95a1

              }}};

    jacobian_point_affine_point_addition(&point_a, &point_b, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_jacobian_point, result_point);
}


void test_jacobian_point_affine_point_addition_1(void)
{
    JacobianPoint result_point;

    JacobianPoint point_a = {
        .x = {.limbs = {
        0x8a06975fe1e8573e,0x4b9cc4973eedf5da,0x2e26d4fecb8e5aac,0x4b1f1d2cfb7992a3

              }},
        .y = {.limbs = {

0x083e03193384122a,0x9722893ba8b06d2d,0xa0031adf59dc392c,0x7763c1f7cd8773e5

              }},
        .z = {.limbs = {

0xcf69ed40987b7ab4,0x0cc69cf344f99c45,0xe4360f36b52e0a10,0x60d9194904049630

              }}};

    Point point_b = {
        .x = {.limbs = {
        0x893b8ba24727ab64,0xdd29679a4a18095f,0xf508b53aec921755,0xf35b4a2aef3ef5f2

              }},
        .y = {.limbs = {

0x8bb1e2ab22ae07cc,0x2cc7a234d8e9cba7,0xf4a6728f829898af,0x5e3d1c56270ccbb5

              }},
    };

    JacobianPoint expected_jacobian_point = {
        .x = {.limbs = {
0xfebdd241fecbaf16,0x7871e5f85aeb07f0,0x2403c9cbde400983,0xa591e3ca4bbfd80b

              }},
        .y = {.limbs = {

0x8f907d7bc5203f50,0x94b277146e551dfa,0x6a7b95698525a378,0x3ae83f6471733c22

              }},

        .z = {.limbs = {

0x7f5821a64664d3bd,0x57ec14c66b7ee660,0xefdaffafa06e6fa1,0xb1374d6a93bb95a1

              }}};

    jacobian_point_affine_point_addition(&point_a, &point_b, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_jacobian_point, result_point);
}


void test_jacobian_point_affine_point_addition_2(void)
{
    JacobianPoint result_point;

    JacobianPoint point_a = {
        .x = {.limbs = {
        0x8a06975fe1e8573e,0x4b9cc4973eedf5da,0x2e26d4fecb8e5aac,0x4b1f1d2cfb7992a3

              }},
        .y = {.limbs = {

0x083e03193384122a,0x9722893ba8b06d2d,0xa0031adf59dc392c,0x7763c1f7cd8773e5

              }},
        .z = {.limbs = {

0xcf69ed40987b7ab4,0x0cc69cf344f99c45,0xe4360f36b52e0a10,0x60d9194904049630

              }}};

    Point point_b = {
        .x = {.limbs = {
        0x893b8ba24727ab64,0xdd29679a4a18095f,0xf508b53aec921755,0xf35b4a2aef3ef5f2

              }},
        .y = {.limbs = {

0x8bb1e2ab22ae07cc,0x2cc7a234d8e9cba7,0xf4a6728f829898af,0x5e3d1c56270ccbb5

              }},
    };

    JacobianPoint expected_jacobian_point = {
        .x = {.limbs = {
0xfebdd241fecbaf16,0x7871e5f85aeb07f0,0x2403c9cbde400983,0xa591e3ca4bbfd80b

              }},
        .y = {.limbs = {

0x8f907d7bc5203f50,0x94b277146e551dfa,0x6a7b95698525a378,0x3ae83f6471733c22

              }},

        .z = {.limbs = {

0x7f5821a64664d3bd,0x57ec14c66b7ee660,0xefdaffafa06e6fa1,0xb1374d6a93bb95a1

              }}};

    jacobian_point_affine_point_addition(&point_a, &point_b, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_jacobian_point, result_point);
}


void test_jacobian_point_affine_point_addition_3(void)
{
    JacobianPoint result_point;

    JacobianPoint point_a = {
        .x = {.limbs = {
        0x8a06975fe1e8573e,0x4b9cc4973eedf5da,0x2e26d4fecb8e5aac,0x4b1f1d2cfb7992a3

              }},
        .y = {.limbs = {

0x083e03193384122a,0x9722893ba8b06d2d,0xa0031adf59dc392c,0x7763c1f7cd8773e5

              }},
        .z = {.limbs = {

0xcf69ed40987b7ab4,0x0cc69cf344f99c45,0xe4360f36b52e0a10,0x60d9194904049630

              }}};

    Point point_b = {
        .x = {.limbs = {
        0x893b8ba24727ab64,0xdd29679a4a18095f,0xf508b53aec921755,0xf35b4a2aef3ef5f2

              }},
        .y = {.limbs = {

0x8bb1e2ab22ae07cc,0x2cc7a234d8e9cba7,0xf4a6728f829898af,0x5e3d1c56270ccbb5

              }},
    };

    JacobianPoint expected_jacobian_point = {
        .x = {.limbs = {
0xfebdd241fecbaf16,0x7871e5f85aeb07f0,0x2403c9cbde400983,0xa591e3ca4bbfd80b

              }},
        .y = {.limbs = {

0x8f907d7bc5203f50,0x94b277146e551dfa,0x6a7b95698525a378,0x3ae83f6471733c22

              }},

        .z = {.limbs = {

0x7f5821a64664d3bd,0x57ec14c66b7ee660,0xefdaffafa06e6fa1,0xb1374d6a93bb95a1

              }}};

    jacobian_point_affine_point_addition(&point_a, &point_b, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_jacobian_point, result_point);
}


void test_jacobian_point_affine_point_addition_4(void)
{
    JacobianPoint result_point;

    JacobianPoint point_a = {
        .x = {.limbs = {
        0x8a06975fe1e8573e,0x4b9cc4973eedf5da,0x2e26d4fecb8e5aac,0x4b1f1d2cfb7992a3

              }},
        .y = {.limbs = {

0x083e03193384122a,0x9722893ba8b06d2d,0xa0031adf59dc392c,0x7763c1f7cd8773e5

              }},
        .z = {.limbs = {

0xcf69ed40987b7ab4,0x0cc69cf344f99c45,0xe4360f36b52e0a10,0x60d9194904049630

              }}};

    Point point_b = {
        .x = {.limbs = {
        0x893b8ba24727ab64,0xdd29679a4a18095f,0xf508b53aec921755,0xf35b4a2aef3ef5f2

              }},
        .y = {.limbs = {

0x8bb1e2ab22ae07cc,0x2cc7a234d8e9cba7,0xf4a6728f829898af,0x5e3d1c56270ccbb5

              }},
    };

    JacobianPoint expected_jacobian_point = {
        .x = {.limbs = {
0xfebdd241fecbaf16,0x7871e5f85aeb07f0,0x2403c9cbde400983,0xa591e3ca4bbfd80b

              }},
        .y = {.limbs = {

0x8f907d7bc5203f50,0x94b277146e551dfa,0x6a7b95698525a378,0x3ae83f6471733c22

              }},

        .z = {.limbs = {

0x7f5821a64664d3bd,0x57ec14c66b7ee660,0xefdaffafa06e6fa1,0xb1374d6a93bb95a1

              }}};

    jacobian_point_affine_point_addition(&point_a, &point_b, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_jacobian_point, result_point);
}

