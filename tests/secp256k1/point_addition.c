#include "structs/point.h"
#include "unity/unity.h"
#include "constants/secp256k1.h"
#include "secp256k1/point_addition.h"

void test_random_point_addition_0(void)
{
    Point result_point;

    Point point_a = {
        .x = {.limbs = {
                  0x1daeea98c0f22efb,
                  0x28d149d8bc512fa7,
                  0xcc2728f5dd03b832,
                  0x6f70ecc2d99a072f,
              }},
        .y = {.limbs = {
                  0xe9370032def04ea5,
                  0xfa674b18f99a8f0d,
                  0x5bf86a6d3f9fa784,
                  0x578817b6053b0554,
              }},
    };

    Point point_b = {
        .x = {.limbs = {
                  0x0ff808b4b1a56370,
                  0xf90b7c166a017022,
                  0xb8fc63ec1c39b4ff,
                  0xfb88d4522aef4030,
              }},
        .y = {.limbs = {
                  0xd0b12c3672f1af15,
                  0xd45b221d74943e7b,
                  0x2736f95b4b2d3c19,
                  0x44eebe3e3216127e,
              }},
    };

    Point expected_point = {
        .x = {.limbs = {
                  0xe3d935c8fe76f7e9,
                  0x6d08a917e8cddaae,
                  0x6690125a827610cd,
                  0xad50dc9860e5729b,
              }},
        .y = {.limbs = {
                  0x466e4bfab8a09a5e,
                  0x1d35fecf4071e240,
                  0x7558d151b5190143,
                  0x37f3c05be2542ea6,
              }},

    };

    point_addition(&point_a, &point_b, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}

void test_random_point_addition_1(void)
{
    Point result_point;

    Point point_a = {
        .x = {.limbs = {
                  0x90c4fe228cd54c9e, 0x444236b266e0fb76, 0xa6694b43c796f76a, 0x5dc0d49c4ba18fc2}},
        .y = {.limbs = {0xb9c34faa59dbab74, 0x12ad2bcdd69eb390, 0x15bf8a261f96ed4a, 0x253b90343d1f651a}},
    };

    Point point_b = {
        .x = {.limbs = {
                  0xc4820e5c28b25364, 0x30d01d83f7501372, 0xbbc6e3a102ce328a, 0xf5cb587fe7df3b4c}},
        .y = {.limbs = {0x30a0869572de42e5, 0x158ed58f4dd40c87, 0xb348e2fd0dfa36dd, 0x12d9b6b5e21de5a1}},
    };

    Point expected_point = {
        .x = {.limbs = {
                  0xd517849123c622f8, 0xbe2d6ed870a28c1c, 0xef973153ac6ccc86, 0xba1309751d9c34d1}},
        .y = {.limbs = {0x101cb70049a7f8d6, 0x3af7f50b3dca529e, 0x60c388d86f534026, 0xfc1009c7dc44b274}},

    };

    point_addition(&point_a, &point_b, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}

void test_random_point_addition_2(void)
{
    Point result_point;

    Point point_a = {
        .x = {.limbs = {
                  0x0143e589704ff524, 0xc071060082721623, 0x2f2b31ab866c3189, 0xe03d0e4d0bad43f8}},
        .y = {.limbs = {0x259710fa43fa4daf, 0x705848f35f4432c7, 0x635ec48cac5bdd2f, 0x0ebe74ee7d30c644}},
    };

    Point point_b = {
        .x = {.limbs = {
                  0xff7aecf6147ae990, 0xc6700857f92c5f78, 0x3d0bfd5bebf72132, 0x4f9230f459e9f064}},
        .y = {.limbs = {0xd382ed7a796cbe01, 0x02a4759ce003ff80, 0xbc0bc987c1e0dbfc, 0x5e0bf34999a958ad}},
    };

    Point expected_point = {
        .x = {.limbs = {
                  0x4336b43c8bfbce25, 0x6b66adccfc2e83fb, 0x94882051af4989df, 0x1823324b838fa29a}},
        .y = {.limbs = {0x64f70eef91a6b98f, 0x8254b634ef7c501b, 0x7c515b6f0a230aca, 0x9e4f2f11a3a54b76}},

    };

    point_addition(&point_a, &point_b, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}

void test_random_point_addition_3(void)
{
    Point result_point;

    Point point_a = {
        .x = {.limbs = {
                  0x30203ea804ead1cd, 0xf7f4e2ec2207bbf8, 0xb948ea1e553a7de0, 0x36d41a23225b5711}},
        .y = {.limbs = {0xf611020e5aceb008, 0x7d21ce6280f0076a, 0xb63030af688d8040, 0x8b7baeb15dfbe090}},
    };

    Point point_b = {
        .x = {.limbs = {
                  0x8c5d433205a11918, 0x1617fe90f72f2a30, 0x42f5e18113542eae, 0x7710f15a3009b5c6}},
        .y = {.limbs = {0x273761bd26dda682, 0x23e41978bd4346b9, 0xf2034462e087ff24, 0xea0bf8bf94461f80}},
    };

    Point expected_point = {
        .x = {.limbs = {
                  0xa04ead5fe7cbd346, 0x5720a03cbac437d1, 0x39a587ee1f1589e2, 0x83441aaf5738624b}},
        .y = {.limbs = {0xcb119cedc6bbf232, 0xee10be15770805d0, 0xcfdc858662df7909, 0x86951791aebdffc1}},

    };

    point_addition(&point_a, &point_b, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}

void test_random_point_addition_4(void)
{
    Point result_point;

    Point point_a = {
        .x = {.limbs = {
                  0x3280855d0b10fc48, 0x0bb25f182da976ae, 0x942bcf6aba9aa624, 0x665bfb9e3bc4f421}},
        .y = {.limbs = {0xc2a2ef8589787912, 0x3754e8dc75419d7d, 0xe2890b524a474432, 0x80dd9be2774e9268}},
    };

    Point point_b = {
        .x = {.limbs = {
                  0x30f41453fa105e54, 0xa4e1606501544714, 0xe752510a323f5288, 0x27e1ea8fafc50fd6}},
        .y = {.limbs = {0xf1e5b89b8f8132f1, 0x55f0951f42837b53, 0xfdfb96d9c2dd32eb, 0x0b64f31e3bd80c42}},
    };

    Point expected_point = {
        .x = {.limbs = {
                  0x672fec485088c73c, 0x452e2a3e590e80e2, 0x3400f870411a107f, 0xa9e3fb72f60e88c7}},
        .y = {.limbs = {0xcfe0ea36a8ae344c, 0x59eb34439f14dbdb, 0x9cce5b27b7f8367c, 0x9a50d12a4f9549db}},

    };

    point_addition(&point_a, &point_b, &result_point);

    ASSERT_POINT_EQUAL(expected_point, result_point);
}
