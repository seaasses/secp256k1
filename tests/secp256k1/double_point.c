#include "structs/point.h"
#include "unity/unity.h"
#include "constants/secp256k1.h"
#include "secp256k1/double_point.h"

void test_double_random_point_0(void)
{
    Point result_point;

    Point point = {
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

    Point expected_point = {
        .x = {.limbs = {
                  0x0df3f827c8189bc2,
                  0xef5b9bf894f9aef8,
                  0xf944c87438009ec9,
                  0x2355408ec9b9504b,
              }},
        .y = {.limbs = {
                  0x9678d0408f65849c,
                  0x945e5313dee7656e,
                  0x1ad1a06ecdbc993e,
                  0xbeb315da2261b4db,
              }},

    };

    double_point(&point, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}

void test_double_random_point_1(void)
{
    Point result_point;

    Point point = {
        .x = {.limbs = {
                  0xa97135d7e6e0798f,
                  0xc595a498b7cf474f,
                  0x6ed999cc5ebeecd6,
                  0xfc7640b5b9fc908a,
              }},
        .y = {.limbs = {
                  0xb06d349e80d31861,
                  0xd3d9ed0bb09f1494,
                  0x7391a9836126c9c7,
                  0x6640a7b3c5e1d869,
              }},
    };

    Point expected_point = {
        .x = {.limbs = {
                  0xa703985e3844291c,
                  0x3cb23bf6caf8a57b,
                  0x18670f791977e087,
                  0xf6ff39970fd0ceb3,
              }},
        .y = {.limbs = {
                  0x3fa8e10a8722e1be,
                  0x7ebedebf18397cb0,
                  0x846f853c2f737ab8,
                  0xd662137c64d97671,
              }},

    };

    double_point(&point, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}

void test_double_random_point_2(void)
{
    Point result_point;

    Point point = {
        .x = {.limbs = {
                  0x32bc0fb805b94799,
                  0x4a9bdf8008b71359,
                  0x19cc184a81e17d8e,
                  0xde10ec0e046f9ccf,
              }},
        .y = {.limbs = {
                  0xcb09620056c6bc23,
                  0x8ff05fb225cc4939,
                  0xc8344b27bec97ffb,
                  0xa59fcf44be5b005d,
              }},
    };

    Point expected_point = {
        .x = {.limbs = {
                  0x80e32721cec4881c,
                  0x3360146e930d5ac1,
                  0x38c1b6567b7ed2a0,
                  0xc32f237879c24a96,
              }},
        .y = {.limbs = {
                  0xb7d3d738d86814ac,
                  0xf19ff314ab3d21df,
                  0x39b2bfd8b271d679,
                  0x3ca0efc2d2b33fc4,
              }},

    };

    double_point(&point, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}

void test_double_random_point_3(void)
{
    Point result_point;

    Point point = {
        .x = {.limbs = {

                  0xbef5f2a51f86a1a1,
                  0x64d769510e5793e2,
                  0xd568187d393a3bbf,
                  0xf59ab0128fd8ceff,

              }},
        .y = {.limbs = {
                  0xda27d547ad9967ce,
                  0x5853324d2c38448e,
                  0x679b2d688b6953c6,
                  0x68a009a3081d9050,

              }},
    };

    Point expected_point = {
        .x = {.limbs = {
                  0xfab0c8dfb4ed894a,
                  0x28e71021dca18451,
                  0x19f986f4aa1d8c3c,
                  0xd0fd9554574ee71a,

              }},
        .y = {.limbs = {

                  0x03bc8c31e6d1258d,
                  0x2c1e9e41edcea07e,
                  0x81aa86aa76556ed2,
                  0x9e9b37295c9ddfeb,
              }},

    };

    double_point(&point, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}

void test_double_random_point_4(void)
{
    Point result_point;

    Point point = {
        .x = {.limbs = {
                  0xc2bab767c7b8cb54,
                  0x40edd1ddec65a01b,
                  0xe9692206f0c45d28,
                  0x4ba53deb7e6fefb8,

              }},
        .y = {.limbs = {

                  0x3b1b69f5302f0df4,
                  0xbaf5d74e23c1f35d,
                  0xad434b6a375e7651,
                  0x707cb4a70a747956,

              }},
    };

    Point expected_point = {
        .x = {.limbs = {
                  0xa32b99818732409e,
                  0x66ebaf91645010b2,
                  0x629f00e8f010217a,
                  0x8bab412893e25cbf,

              }},
        .y = {.limbs = {

                  0x4bae5eaff7b13af5,
                  0xd8cb977ba8d8f4c1,
                  0x5636c5ca1a53d89e,
                  0x5a19b32104d9fb54,
              }},

    };

    double_point(&point, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}