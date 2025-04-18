#include "structs/point.h"
#include "unity/unity.h"
#include "constants/secp256k1.h"
#include "secp256k1/jacobian_to_affine.h"

void test_jacobian_to_affine_z_is_1(void)
{
    Point result_point;

    JacobianPoint point = {
        .x = {.limbs = {
                  0xc7155087b7fd3046,
                  0x65140b0dbc5c86de,
                  0x4ecb3d0750f6df7a,
                  0x8ba09704d4a99900,
              }},
        .y = {.limbs = {
                  0x2d9b0a39a0c2e636,
                  0x7496023f1589d0bd,
                  0xa7793b4b2312ec94,
                  0x5676372262af7fb8,
              }},
        .z = {.limbs = {0, 0, 0, 1}}};

    Point expected_point = {
        .x = {.limbs = {
                  0xc7155087b7fd3046,
                  0x65140b0dbc5c86de,
                  0x4ecb3d0750f6df7a,
                  0x8ba09704d4a99900,
              }},
        .y = {.limbs = {
                  0x2d9b0a39a0c2e636,
                  0x7496023f1589d0bd,
                  0xa7793b4b2312ec94,
                  0x5676372262af7fb8,
              }},
    };

    jacobian_to_affine(&point, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}

void test_jacobian_to_affine_random_point_0(void)
{
    Point result_point;

    JacobianPoint point = {
        .x = {.limbs = {

                  0x30378d8474ed00b0, 0x5b0e8174fd697f3a, 0x7a0a094b7dbd273e, 0x042b7b5f3934d081

              }},
        .y = {.limbs = {

                  0x48785b34511221e9, 0x7e3379b90f26bc2f, 0x74c327016f885311, 0xd57a7308b34da8ae

              }},
        .z = {.limbs = {

                  0x0c5e4b33b4afbd0a, 0xa786401db23bf490, 0xad70d25c38e0ede6, 0x8916d73621f61597

              }}};

    Point expected_point = {
        .x = {.limbs = {
                  0x2d5fdbc89b85b9f4, 0x3cfd11f584064c24, 0x524f21fe48d78e34, 0x870e93ba076302d0

              }},
        .y = {.limbs = {

                  0x48a46033f4205876, 0xc4a8e66295c2221a, 0xd339009db71294ae, 0x69dbef27b5aa56f8

              }},
    };

    jacobian_to_affine(&point, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}

void test_jacobian_to_affine_random_point_1(void)
{
    Point result_point;

    JacobianPoint point = {
        .x = {.limbs = {

                  0x445fee4b2916a036, 0xea6e6e71394982a5, 0xeec64c695b54e579, 0xad89de425a581eb2

              }},
        .y = {.limbs = {

                  0xc8b7ee197c998226, 0x90b1d546d3c87351, 0x649b3aeb1077ed6b, 0x5ea1e0a928cb4120

              }},
        .z = {.limbs = {

                  0xffa54c71163a52d4, 0xd4eb327009ef3b37, 0xecfa42efbe914f46, 0xf8d781076df53686

              }}};

    Point expected_point = {
        .x = {.limbs = {
                  0x01ea33875aee20cc, 0xa8bd8f336fde3104, 0xb3bb4d9bc5113e45, 0xeed0c0fde32ecdfe

              }},
        .y = {.limbs = {

                  0xac9498e7bff24d82, 0xa5ceff4120aa9caa, 0x14f5ae85115fa310, 0x42007ca595be18ff

              }},
    };

    jacobian_to_affine(&point, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}

void test_jacobian_to_affine_random_point_2(void)
{
    Point result_point;

    JacobianPoint point = {
        .x = {.limbs = {

                  0xbe4cd1e6dea7b64c, 0xd0db7f0a907b4dd3, 0x6ed82bef457aab10, 0x5bd0cd4aca7ae9b9

              }},
        .y = {.limbs = {

                  0x0345ffe44c21d878, 0xc3bdf9ae7a6f4309, 0xa46a4424c95381c7, 0x918b7db895cc5949}},
        .z = {.limbs = {

                  0xeccc288ad14367be, 0x878073e56b8fe7a9, 0xa6c7bc4ad76c82dd, 0x4802babb7f230621

              }}};

    Point expected_point = {
        .x = {.limbs = {
                  0x4b73d15a96328fe1, 0x80b29d5f09d20231, 0xb91aed291a4a10a3, 0x6d7625e88fd93042

              }},
        .y = {.limbs = {

                  0x2d8d25352c678c39, 0x723db7a70779f4c2, 0xed0c80bb865138bb, 0x5efdf87ae8a62cd7

              }},
    };

    jacobian_to_affine(&point, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}

void test_jacobian_to_affine_random_point_3(void)
{
    Point result_point;

    JacobianPoint point = {
        .x = {.limbs = {

                  0x034b490ec3cc303a, 0x15235aa805c83a44, 0x32840940f53e5d0c, 0xd050d8c85f2e21c9

              }},
        .y = {.limbs = {

                  0x08ddbdd0abd47a34, 0xa2463602c07dc0be, 0x6931b62ba6d8b3eb, 0xc4b6e272e80af3ce

              }},
        .z = {.limbs = {

                  0x47d351a1f2148c89, 0x733904d8f1333081, 0x6954d081e5da477c, 0x097d0671bf1b4dbb

              }}};

    Point expected_point = {
        .x = {.limbs = {
                  0xbe74f08882ded4aa, 0xcb0df0ae71ffef83, 0x139e6950246d2f7c, 0x4518c7a840d955cc

              }},
        .y = {.limbs = {

                  0x840eb8f8ce3d6f7a, 0xb886bc34e1294ebd, 0x0ebba7cf8969d6af, 0xe4c9ea35a129a83d

              }},
    };

    jacobian_to_affine(&point, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}

void test_jacobian_to_affine_random_point_4(void)
{
    Point result_point;

    JacobianPoint point = {
        .x = {.limbs = {

                  0x52e1b8d88bd606de, 0xd319958c45f07ff3, 0xce2009581e4f25a2, 0x85ab19fab44a3839

              }},
        .y = {.limbs = {

                  0xe61af2d9e72e9210, 0x4c53b39d228d9dac, 0xe8c1f985ed95f48a, 0xe16f355e0b103d66

              }},
        .z = {.limbs = {

                  0xae648c462a4d2b57, 0x2b23f4e6806d9dfd, 0x27400f80e2274427, 0x22d1e4afbdc2d4ae

              }}};

    Point expected_point = {
        .x = {.limbs = {
                  0xe4615459bc38012d, 0x4c80fcdd0589535e, 0x410e120597e987c8, 0xe9754f40901287e9

              }},
        .y = {.limbs = {

                  0x0c9c30babfcc04a8, 0x2553cf4c1e84fe76, 0xaff093e83bba7343, 0x9dbd458d0120e056

              }},
    };

    jacobian_to_affine(&point, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}