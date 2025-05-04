#include "structs/point.h"
#include "unity/unity.h"
#include "secp256k1/jacobian_to_affine.h"

void test_jacobian_to_affine_z_1(void)
{
    Point result_point;

    JacobianPoint point = {
        .x = {.limbs = {
                  0x8479780fa0f53458, 0x1a8ba3cb543bc5f7, 0xecf776141af74cf8, 0x8bd3e9fbc76aced8}},
        .y = {.limbs = {0x2bc0b1a41a002a4b, 0xe1dd6a21ac96ca32, 0x8381e2e3ae1ca900, 0x3fa81a7eff0035f3}},
        .z = {.limbs = {0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000001}}};

    Point expected_point = {
        .x = {.limbs = {
                  0x8479780fa0f53458, 0x1a8ba3cb543bc5f7, 0xecf776141af74cf8, 0x8bd3e9fbc76aced8}},
        .y = {.limbs = {

                  0x2bc0b1a41a002a4b, 0xe1dd6a21ac96ca32, 0x8381e2e3ae1ca900, 0x3fa81a7eff0035f3}},
    };

    jacobian_to_affine(&point, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}

void test_jacobian_to_affine_0(void)
{
    Point result_point;

    JacobianPoint point = {
        .x = {.limbs = {
                  0x544bdff14e4c32ac, 0xee3bcb34d15da808, 0xf93f2bb61083ea38, 0x9a5669a80a2695c8}},
        .y = {.limbs = {0x86d33c6cd4ac61d5, 0x11d1e061fd0e426b, 0x10333aa1b00beeee, 0xb176d93ac327e08b}},
        .z = {.limbs = {0xdf8d054cff98bffd, 0x27a3bff36b2370a2, 0x0c250d381e94d55c, 0xdd50844bfb51ddf7}}};

    Point expected_point = {
        .x = {.limbs = {
                  0x1a44e4aaf2cecece, 0x951418a46d6df3eb, 0xa2961a62d961c56f, 0x250ec1334b671189}},
        .y = {.limbs = {0x3a67e94474826ca0, 0x5e81fb9e28fdf428, 0xd9deede60429b450, 0x723e4c9e56d7723c}},
    };

    jacobian_to_affine(&point, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}

void test_jacobian_to_affine_1(void)
{
    Point result_point;

    JacobianPoint point = {
        .x = {.limbs = {
                  0xe5ac984154296d20, 0xab9afb53672b7116, 0xf01c31d04f0fa5f4, 0x59d00191b790f65a}},
        .y = {.limbs = {0xbefcbe3ca8ad9f4f, 0x6a6a73bd6807c22c, 0x38560da0c2c9b7de, 0x68be6e736f76b02f}},
        .z = {.limbs = {0x34e31e55625ef38b, 0xcbe8d3209b2084c5, 0x33b43ef8d48ba5f5, 0x9ec40fc889129a32}}};

    Point expected_point = {
        .x = {.limbs = {
                  0xfdfefd528f226838, 0x274f185b6ac0a510, 0x13f0d4e8747d0978, 0x2d6f7993755d2ca3}},
        .y = {.limbs = {0x597b49799fb96d9c, 0xbefc5c3fba258722, 0x73a4599e301be161, 0xc6ec00ecc71cc225}},
    };

    jacobian_to_affine(&point, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}

void test_jacobian_to_affine_2(void)
{
    Point result_point;

    JacobianPoint point = {
        .x = {.limbs = {
                  0x8604bcfb78d109d2, 0x4ebb4e321974ddbf, 0x2ebe06ae6d6e4e2b, 0x8110f2773c57726a}},
        .y = {.limbs = {0x189eea62a1bebd6c, 0x2d6e28d82fd1c4cb, 0x1274a4fca6f3b6fb, 0xfca317ed43fedc4f}},
        .z = {.limbs = {0x2a1f70952f8715ea, 0x93862e1071d9a98c, 0x1b6c5186053d8f61, 0x730ea48dc375685f}}};

    Point expected_point = {
        .x = {.limbs = {
                  0xbbe7ac02a22c27a6, 0xe87913c7a49dcb9f, 0x0708a0cc3f86f31d, 0xf7003647917d2d5c}},
        .y = {.limbs = {0xa8d3a48a8f2b703b, 0xca105c612d98abba, 0xfbc64a85acaa9b89, 0x0ec6ce3a68374655}},
    };

    jacobian_to_affine(&point, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}

void test_jacobian_to_affine_3(void)
{
    Point result_point;

    JacobianPoint point = {
        .x = {.limbs = {
                  0xdfbbd887401447cd, 0x4280a7e3577c749c, 0xa793f6d247c60986, 0x80d71dea4c5f69fb}},
        .y = {.limbs = {0x69762f7a53ecc5d5, 0x785e44cef80649fb, 0x6a32bd517000bb25, 0xb5f6e9d810ca66fa}},
        .z = {.limbs = {0xd950ccc27f2ba21c, 0xbd7bda4bd3577140, 0x3fcdf17fd04ce04b, 0x05dd0cc1dbd5d940}}};

    Point expected_point = {
        .x = {.limbs = {
                  0xbfad569532a0b570, 0x70c076394f490fab, 0x477864c53053273b, 0x9b02f61328e78847}},
        .y = {.limbs = {0x74c0ac5f19effcbe, 0xe382f7d5bb252bac, 0x0a05465bc96ffd4e, 0xbe8682b3b6e881ea}},
    };

    jacobian_to_affine(&point, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}

void test_jacobian_to_affine_4(void)
{
    Point result_point;

    JacobianPoint point = {
        .x = {.limbs = {
                  0x966834e8713f72c9, 0x440dfcd0e9d3ac09, 0x77bb5e3c5a029deb, 0x03a933a026c048db}},
        .y = {.limbs = {0x3fb132780b138ddc, 0xa60d8d53ad1b8d3e, 0xa347adf0de047c45, 0xe748690ae1805637}},
        .z = {.limbs = {0xbe4893708bec87c6, 0x32e51544a6ecd187, 0x40220a7c16aa9cff, 0xbb8fb2a8f467496e}}};

    Point expected_point = {
        .x = {.limbs = {
                  0xafeb998a3a31d317, 0x959b728b06c88cc7, 0xb2258bc7667a86e0, 0x6a5ac15e450b8377}},
        .y = {.limbs = {0x7576e86e198ff7d0, 0x220942ef9c2e6aa6, 0xa1a11945392ff4b0, 0x33cc731c2720f87f}},
    };

    jacobian_to_affine(&point, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}
