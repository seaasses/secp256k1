#include "structs/point.h"
#include "unity/unity.h"
#include "constants/secp256k1.h"
#include "secp256k1/jacobian_point_addition_jacobian_plus_affine.h"

void test_jacobian_point_addition_jacobian_plus_affine_0(void)
{
    JacobianPoint result_point;

    JacobianPoint point_a = {
        .x = {.limbs = {
                  0xc30728b26add3644, 0xce85ca1ea6ac3258, 0xeae95287e07b8e46, 0x72af3114a8e9b479

              }},
        .y = {.limbs = {

                  0x3d59edd5810fbba7, 0xbeae03e136057178, 0x06d9ff9e22a4dbb2, 0xaaa046f4f20eaecd

              }},
        .z = {.limbs = {

                  0xdc8f47273df5723a, 0xf015ef781fb6e56b, 0xc8c5e3bc2b2a01ce, 0xe1950b541780a320

              }}};

    Point point_b = {
        .x = {.limbs = {
                  0xae2010f7376d7407, 0x022dedac1562180d, 0x00c00fe43fc326db, 0xcff62f35e3685cc9

              }},
        .y = {.limbs = {

                  0x22c92ac32de65962, 0xa8b44ad03d7d8c16, 0x619fabc1c8c1f6a5, 0x4b763b4b71eafbc0

              }},
    };

    JacobianPoint expected_jacobian_point = {
        .x = {.limbs = {
                  0xfd15b32360908542, 0x0da42abb70b2da0b, 0x6411f9d20e867348, 0x347e48cc13c3f9bd

              }},
        .y = {.limbs = {

                  0xff6932a98fd0ab7b, 0xb523f6a196d11d9c, 0x16e251bfab1b616b, 0x07c83b69c187562b

              }},

        .z = {.limbs = {

                  0xaeaf02b9d292271d, 0xc3fcc7318991a443, 0xa81bcd359474b487, 0xb83ff0082375ea38

              }}};

    jacobian_point_addition_jacobian_plus_affine(&point_a, &point_b, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_jacobian_point, result_point);
}

void test_jacobian_point_addition_jacobian_plus_affine_1(void)
{
    JacobianPoint result_point;

    JacobianPoint point_a = {
        .x = {.limbs = {
                  0x68c0646cc14a696d, 0x5a4758fa77d76f4f, 0x502cbf06cdb770b5, 0x2cd2deffd78814b3

              }},
        .y = {.limbs = {

                  0x103f7b4eede1ae87, 0xc013a95c5441157f, 0xdd41bbea13272536, 0x2882461bb315b6e7

              }},
        .z = {.limbs = {

                  0xdd5c922a1ecb8b02, 0xb113c0371b0fc24c, 0x0d076ee69c758664, 0x0a3d2c1afb4a3a2a

              }}};

    Point point_b = {
        .x = {.limbs = {
                  0x032297ea9aff0ae7, 0x0b6cb7277e97930f, 0xa08c093b33cbf067, 0x374a67d36776c95e

              }},
        .y = {.limbs = {

                  0xea69cbf5145fc71c, 0x969fbb23cf7541a9, 0x671945aa491f624a, 0x7b61ad5999e23c70

              }},
    };

    JacobianPoint expected_jacobian_point = {
        .x = {.limbs = {
                  0x9686211d7ac2c4f3, 0x7ca95da1e4e9f7af, 0x45f592901a6cd069, 0xce005c6a9993fd8d

              }},
        .y = {.limbs = {

                  0xb334672b9dd96168, 0x7a4ff84fac62f140, 0xdbc72c0dbcfbbd54, 0x33193567891544f1

              }},

        .z = {.limbs = {

                  0x75041480a214c7c2, 0x3eaa4ed341eb1ece, 0xadad85d6de351412, 0x6c9a3767ab51de7d

              }}};

    jacobian_point_addition_jacobian_plus_affine(&point_a, &point_b, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_jacobian_point, result_point);
}

void test_jacobian_point_addition_jacobian_plus_affine_2(void)
{
    JacobianPoint result_point;

    JacobianPoint point_a = {
        .x = {.limbs = {
                  0xfde7dcc9a979f49e, 0x53752e887755df3e, 0x7a976bd99fdc1a14, 0xebfe3501912b78cc

              }},
        .y = {.limbs = {

                  0xf7d98c976c85706b, 0xb5e3cc97d2aff1f8, 0xf00ef6fd5e6110ff, 0xaeffce07e9b25690

              }},
        .z = {.limbs = {

                  0x7731145b68ddd400, 0xeb4da5d3dcdd0376, 0x8ceb5fd1e2d231cf, 0x26b7009ab0b88223

              }}};

    Point point_b = {
        .x = {.limbs = {
                  0x52e7a31f49acc7f4, 0x81576e1b329ee561, 0x90d4c5b48f2bf661, 0x1d13c2953a234c52

              }},
        .y = {.limbs = {

                  0xa47ad89e9b5843b1, 0xb5bf71df6081d7ee, 0xad23a941abb13db4, 0xd03f499f09c5bfe9

              }},
    };

    JacobianPoint expected_jacobian_point = {
        .x = {.limbs = {
                  0xc607f8949cf77874, 0x3d00857b22550a79, 0x71625af2d6de7940, 0xaed9daf20159da24

              }},
        .y = {.limbs = {

                  0xc9bcc256765b61d5, 0x8900e5f66b5f5114, 0x64b279b2945abc38, 0xa1e8a1ec72837963

              }},

        .z = {.limbs = {

                  0x1a2ab72354800d69, 0x9ea23d6171526a63, 0x814cbbfc9bed6c85, 0xf4678deb10db96d5

              }}};

    jacobian_point_addition_jacobian_plus_affine(&point_a, &point_b, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_jacobian_point, result_point);
}
void test_jacobian_point_addition_jacobian_plus_affine_3(void)
{
    JacobianPoint result_point;

    JacobianPoint point_a = {
        .x = {.limbs = {
                  0xd15e5540452ac39a, 0x2579a4adebdd6176, 0x4e4934a0eba6a306, 0x83501b5f78c47765

              }},
        .y = {.limbs = {

                  0xb12e95417fe9ac82, 0x9cff7dd0a16e240d, 0xf642b5bf68c29175, 0x62fbd46298156fdb

              }},
        .z = {.limbs = {

                  0xf96f242158b503f6, 0xb3141585aac0a9ec, 0xcd806c2b5650c165, 0xec6691b674e78b25

              }}};

    Point point_b = {
        .x = {.limbs = {
                  0xc6da92bf820ff5b8, 0x3915761c5fa7880b, 0x67c644db782f5fe5, 0xaf472db888205805

              }},
        .y = {.limbs = {

                  0x6d8f511cd5fafc06, 0x6e4ed9fc2eaa70a2, 0x003cdc3b0b4e8896, 0xf0da0c7488060dbd

              }},
    };

    JacobianPoint expected_jacobian_point = {
        .x = {.limbs = {
                  0x573bd2e0bdc77e68, 0x39d8fe8db59e9fd8, 0x1483b51bb5817c2e, 0x054a9429b27e3310

              }},
        .y = {.limbs = {

                  0x039096b8b5d6342e, 0x6d3eedbf3fdad175, 0x52e94a32c5ddeadf, 0xdcf967c13c5d25e1

              }},

        .z = {.limbs = {

                  0x9c6e8920a0fa85a4, 0x02b365ebc99774d5, 0x2afc8fbe01c0ac4f, 0x985feb79218ab74c

              }}};

    jacobian_point_addition_jacobian_plus_affine(&point_a, &point_b, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_jacobian_point, result_point);
}
void test_jacobian_point_addition_jacobian_plus_affine_4(void)
{
    JacobianPoint result_point;

    JacobianPoint point_a = {
        .x = {.limbs = {
                  0x11f5836d30c3bcab, 0xdfda5be346791e22, 0xfa74f52c6359e6b5, 0x3f208fbb6efdeb5f

              }},
        .y = {.limbs = {

                  0x394005e7efb455c6, 0x7e755b707319fee3, 0x3d7dae6eef55963b, 0xf9c2a8417f967664

              }},
        .z = {.limbs = {

                  0x6f757c8d094cbacb, 0x4722455f50439eb4, 0x708678c05a7a8b72, 0x73e0a53311d83dd8

              }}};

    Point point_b = {
        .x = {.limbs = {
                  0xc665342cd8410e47, 0x545ab66fae329cae, 0x19a934afc46a639c, 0x37d44c4013f3272f

              }},
        .y = {.limbs = {

                  0xcfbf997b696be0c0, 0xff870db9437c5da3, 0x61f5db6700cec99a, 0xc8168e296f2cd3c9

              }},
    };

    JacobianPoint expected_jacobian_point = {
        .x = {.limbs = {
                  0x1d311f6fb845b2f4, 0xbc66b85dbe583c94, 0x14d45cb22ac49223, 0xaf676c4ae7af80d0

              }},
        .y = {.limbs = {

                  0x07d48a787cf07dfe, 0x0134775f931b3b61, 0x963606b6847a7d86, 0x32a63b422190559b

              }},

        .z = {.limbs = {

                  0x7e75041d75a89517, 0x9432e1650d5067f1, 0xb0184f90b67a10e9, 0xb0e8e8c47bcaff8d

              }}};

    jacobian_point_addition_jacobian_plus_affine(&point_a, &point_b, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_jacobian_point, result_point);
}