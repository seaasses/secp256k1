#include "structs/point.h"
#include "unity/unity.h"
#include "constants/secp256k1.h"
#include "secp256k1/jacobian_double_point.h"

void test_jacobian_double_point_z_is_1(void)
{
    JacobianPoint result_point;

    JacobianPoint point = {
        .x = {.limbs = {
                  0xce043e5eac11eb16, 0x85ddb85cc7065ec9, 0x5265f0df9e986851, 0x779007e0a58aeab9

              }},
        .y = {.limbs = {0xb83d2dea6e8fc85d, 0x126db0c68707adc8, 0xc4b8e32f400e64e6, 0x9a1f639bb788aa0f}

        },
        .z = {.limbs = {0, 0, 0, 1}}};

    JacobianPoint expected_jacobian_point = {
        .x = {.limbs = {
                  0x02ef05f0a21cf642, 0x2e4bcd0444f99501, 0x6897ed2253c7a129, 0xef2e35e99ebbb40f

              }},
        .y = {.limbs = {

                  0xae8a3b42566c37de, 0x6edf5a86b1579dd0, 0x512eb644988667b3, 0xa274d42caa23a3e9

              }},

        .z = {.limbs = {

                  0x707a5bd4dd1f90ba, 0x24db618d0e0f5b91, 0x8971c65e801cc9cd, 0x343ec7386f1157ef

              }}};

    jacobian_double_point(&point, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_jacobian_point, result_point);
}

void test_jacobian_double_random_point_0(void)
{
    JacobianPoint result_point;

    JacobianPoint point = {
        .x = {.limbs = {
                  0x05f74357d15a75a2, 0x622aab57db669ec6, 0x9f109d4877e4d1a5, 0x3f83b03467e1bd6f

              }},
        .y = {.limbs = {0xf36eaf3fcd29130c, 0xbdcdacf396acea4c, 0x3dcce922f66efcc4, 0x579b7ede57a8377b}

        },
        .z = {.limbs = {

                  0x66b533ecd64d449c, 0x9789e6d03326e839, 0xf7a8e2529c600799, 0xab74864e7c50697b}}};

    JacobianPoint expected_jacobian_point = {
        .x = {.limbs = {
                  0x80dbf1c163b18b1f, 0x8d9191a42b667a55, 0x8653c8118a262149, 0x153d1eb42ac11d1d

              }},
        .y = {.limbs = {

                  0x1dfb4f304c8ae6de, 0x51e9dbf8ac88d9f9, 0xdc2dd1bcf74399cc, 0xfee4c0ff6c7f15a1

              }},

        .z = {.limbs = {

                  0xd3eb8c0a51afdc29, 0x311f5e155785bc26, 0xe92f3e1f81a17f04, 0x4f11a88b194998d0

              }}};

    jacobian_double_point(&point, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_jacobian_point, result_point);
}

void test_jacobian_double_random_point_1(void)
{
    JacobianPoint result_point;

    JacobianPoint point = {
        .x = {.limbs = {
                  0x91f435f7ad3fc8c9, 0x055d8b027e3ba25e, 0xa8a99c20b4e1be5e, 0x0a05ba8474525ac1}},
        .y = {.limbs = {0x1df562d25f9f9a15, 0xbf691ca973fd2dc0, 0x4e1bd00cd5d3f2ff, 0xb2677dd16b4ca3d3}

        },
        .z = {.limbs = {

                  0xf8632feff12d0c30, 0x33dbe969097eaf44, 0xfe319fe38e792d52, 0xe93512cdd115af05}}};

    JacobianPoint expected_jacobian_point = {
        .x = {.limbs = {
                  0x588497bfccc23d9f, 0x8bd0da67c8c5cc5f, 0xbcc8a8a1a895a0ca, 0xd8ec0a64b7d3d8e8

              }},
        .y = {.limbs = {

                  0xca4156de9f7ffe80, 0x957931c23054e4ab, 0xc6c0bddefc6b6e92, 0x944549a3c6e51e0c

              }},

        .z = {.limbs = {

                  0xb44389822e4e7dfe, 0x282a368785711778, 0x12dce7e320f786b7, 0x59da3882d4cba276

              }}};

    jacobian_double_point(&point, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_jacobian_point, result_point);
}

void test_jacobian_double_random_point_2(void)
{
    JacobianPoint result_point;

    JacobianPoint point = {
        .x = {.limbs = {
                  0xa14634d6d0580109, 0x9a53c246c87d8acd, 0xecd33cf6abf10107, 0xc6b71eb1c5d54d04}},
        .y = {.limbs = {0x7a6b45cba844e941, 0xac7731bd8c562149, 0x623fc2ec94ee6c6e, 0x34170b066ac277ba}

        },
        .z = {.limbs = {

                  0xd0c7aba2ece4b3d5, 0x7adc0b8f546f2732, 0xd53d7c42159e6667, 0xd911ebf51a7e2a1e}}};

    JacobianPoint expected_jacobian_point = {
        .x = {.limbs = {
                  0xdb6d6b36d74b0321, 0xd10f9c27a112a777, 0xba2368feca543c40, 0x0bf1fa834eb90162

              }},
        .y = {.limbs = {

                  0x4b197745613fed69, 0xcce0b0f15ded8f05, 0xd80bfbbbba648542, 0x7c5029f2eb6cd149

              }},

        .z = {.limbs = {

                  0x98c80d0f4482f3cf, 0xff66131be2c8298b, 0x43f6a6aeded69333, 0xf40174b65b9fc75d

              }}};

    jacobian_double_point(&point, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_jacobian_point, result_point);
}

void test_jacobian_double_random_point_3(void)
{
    JacobianPoint result_point;

    JacobianPoint point = {
        .x = {.limbs = {
                  0x1cde1407e0c0e6f6, 0xc9227e000c1c3fd8, 0x42ad40cb6326d6f6, 0xf1afd0c4d9b4a652}},
        .y = {.limbs = {0x73699a9a3e35de3a, 0x2bef431a7e0c3833, 0xd47ff1c0515b3511, 0xd1733f8ba7b663cd}

        },
        .z = {.limbs = {

                  0x14de639257634d9f, 0xd173ca34c0497b2f, 0x09cdfad17392f85f, 0x94ffafea8f088b24}}};

    JacobianPoint expected_jacobian_point = {
        .x = {.limbs = {
                  0xc7d72d0505cd1fbb, 0xec6e9a71a0a39e91, 0x684c48535d3ca007, 0xea2d994bef3a15c2

              }},
        .y = {.limbs = {

                  0x2a9a5c37917f5980, 0x0585045ee0e8f8a5, 0xe5eae03bdb7f71ee, 0x1d952540cf55dc4a

              }},

        .z = {.limbs = {

                  0x2830c4bee807e515, 0x432613614441b171, 0x90130bdcda75b8e2, 0x8a292f57c901bd46

              }}};

    jacobian_double_point(&point, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_jacobian_point, result_point);
}
