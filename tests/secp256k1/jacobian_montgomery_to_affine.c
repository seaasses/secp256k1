#include "structs/point.h"
#include "unity/unity.h"
#include "constants/secp256k1.h"
#include "secp256k1/jacobian_montgomery_to_affine.h"

void test_jacobian_montgomery_to_affine_random_point_0(void)
{
    Point result_point;

    JacobianPoint point = {
        .x = {.limbs = {
            0x89dcc3f8c66fbf50,0xbd500c3bf45b1243,0x0331a752b6ef0b0a,0x3d024396f2e5a505
              }},
        .y = {.limbs = {
0xc6ccbe119db04f71,0xa201b290812ee461,0xfb77d6c7b9355a0c,0xa094328e7bd7c56d
              }},
        .z = {.limbs = {
0x1ced4db34665269c,0x404c4a2a4a629afb,0x0f8f48af39217099,0xb288a46cb9fc945b
}}};

    Point expected_point = {
        .x = {.limbs = {
0x09f430fd059c33ec,0x96ca7c1efc05a90f,0x5d45ce63e3a315e2,0x2d46d94b2e26eabb
              }},
        .y = {.limbs = {
0xe8d8c2b16b7c7170,0xcaa24a1bd39678b2,0xa859a20af708be1d,0x1b3b9b45330f82de
              }},
    };

    jacobian_montgomery_to_affine(&point, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}


void test_jacobian_montgomery_to_affine_random_point_1(void)
{
    Point result_point;

    JacobianPoint point = {
        .x = {.limbs = {
            0x89dcc3f8c66fbf50,0xbd500c3bf45b1243,0x0331a752b6ef0b0a,0x3d024396f2e5a505
              }},
        .y = {.limbs = {
0xc6ccbe119db04f71,0xa201b290812ee461,0xfb77d6c7b9355a0c,0xa094328e7bd7c56d
              }},
        .z = {.limbs = {
0x1ced4db34665269c,0x404c4a2a4a629afb,0x0f8f48af39217099,0xb288a46cb9fc945b
}}};

    Point expected_point = {
        .x = {.limbs = {
0x09f430fd059c33ec,0x96ca7c1efc05a90f,0x5d45ce63e3a315e2,0x2d46d94b2e26eabb
              }},
        .y = {.limbs = {
0xe8d8c2b16b7c7170,0xcaa24a1bd39678b2,0xa859a20af708be1d,0x1b3b9b45330f82de
              }},
    };

    jacobian_montgomery_to_affine(&point, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}


void test_jacobian_montgomery_to_affine_random_point_2(void)
{
    Point result_point;

    JacobianPoint point = {
        .x = {.limbs = {
0x98d8ad8189890c61,0xdb7b691a7c0aa3f7,0x03a92197a37d6d0b,0xadc6f887b0269e99
              }},
        .y = {.limbs = {
0x6cb1edb0bfd810ad,0x785ffc3456a58d04,0x3b5e643eb8993b2c,0x4b34e63d14e00000
              }},
        .z = {.limbs = {
0x4f0345c3ae4cc109,0x67cbb2d81f7ded5b,0x53c3458e9b672904,0x2a064538a5729316
}}};

    Point expected_point = {
        .x = {.limbs = {
0xd84494a78a711403,0x1831392e334d35ac,0x169aa7233299ce60,0xe18e74e9065f1737
              }},
        .y = {.limbs = {
0x5621d95c8e58d5d2,0xaf5990a447b109a7,0xd61ecdea9a83ed0e,0x49f7cdbb3a5b2cc8
              }},
    };

    jacobian_montgomery_to_affine(&point, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}

void test_jacobian_montgomery_to_affine_random_point_3(void)
{
    Point result_point;

    JacobianPoint point = {
        .x = {.limbs = {
0x5de7a9486bd887bb,0xaaa54566bdaa8aa9,0x2a0c0e1ede8823c1,0x6be75618d662a9b4
              }},
        .y = {.limbs = {
0x4f99125a0a89a52f,0x7e6b4e0c58d6a58b,0x98f5f43450b7d6c9,0xc5880345a5f8d953
              }},
        .z = {.limbs = {
0x57857d646f279b85,0x4705f9cea540fa20,0xffb432725c93cd30,0xad1ef73b6dfd4e4a
}}};

    Point expected_point = {
        .x = {.limbs = {
0xc52a7d9b4bc0e9ff,0xbc1c56c49ea4e768,0x4fa5990a72cd1eb7,0xad5fe7e0b4812f52
              }},
        .y = {.limbs = {
0x200e2c414c38e70f,0x12ec4f24acc35abc,0x87b3fc24020e667f,0x5598af58e96a77a1
              }},
    };

    jacobian_montgomery_to_affine(&point, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}

void test_jacobian_montgomery_to_affine_random_point_4(void)
{
    Point result_point;

    JacobianPoint point = {
        .x = {.limbs = {
0x6d09d7478a29a548,0xf117d607f24c3623,0x10a63620ea29380b,0x7d9e03116d61c72e
              }},
        .y = {.limbs = {
0x8b018bff1c3904db,0x39dcbea6eb8ee7e4,0x36c92fd95a29de56,0xd86b5f1bd6705a3e
              }},
        .z = {.limbs = {
0x1175ba143cd70058,0x63bfb92c3ed64f26,0x3606b1903c3a6c0f,0x15c576306e668b4d
}}};

    Point expected_point = {
        .x = {.limbs = {
0xae5305be615463b9,0x4f6ff486550e246e,0x05ed7c57277ed009,0x4dfd6e0dcf371683
              }},
        .y = {.limbs = {
0x85265d437e2d6837,0x3fcca8ab28bc77f1,0xe2bba218a2d2ff1a,0x3628248437f484dc
              }},
    };

    jacobian_montgomery_to_affine(&point, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}