#include "structs/point.h"
#include "unity/unity.h"
#include "constants/secp256k1.h"
#include "secp256k1/jacobian_point_addition.h"

void test_jacobian_point_addition_z_is_1(void)
{
    JacobianPoint result_point;

    JacobianPoint point_a = {
        .x = {.limbs = {
                  0xc6606c90bec07095, 0x95dd2ba3ed7a4a64, 0x56a09f70d31c9545, 0x937e1dd3c6e62396}},
        .y = {.limbs = {0x06a6c4205ad6444b, 0xf49f2edcdc8d5d8b, 0x9d11a50e22311704, 0xe7e0240393e449f5}},
        .z = {.limbs = {0, 0, 0, 1}}};

    JacobianPoint point_b = {
        .x = {.limbs = {
                  0x5ae386c32ac58206, 0x019a5d0c6c74b2fc, 0x92388899ed34ecb6, 0xca1b5162a97b4457

              }},
        .y = {.limbs = {0x02e0543e999c67d0, 0x49b6da5482f02149, 0x5b132285d66c7ca5, 0x9cee9e1c25cc10eb}},
        .z = {.limbs = {0, 0, 0, 1}}};

    JacobianPoint expected_jacobian_point = {
        .x = {.limbs = {
                  0xae335c7bbac4937c, 0xf25a6147916cf1f1, 0x186194400da9b14b, 0xb613352456c6aabd

              }},
        .y = {.limbs = {0x3ee9d590ed822bfc, 0x6323f4276725f22a, 0x2d6ef178f96c9d7d, 0x48503e404980906d

              }},

        .z = {.limbs = {0x29063464d80a22e0, 0xd77a62d0fdf4d130, 0x772fd2523430aee2, 0x6d3a671cc52a3db1}}};

    jacobian_point_addition(&point_a, &point_b, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_jacobian_point, result_point);
}

void test_jacobian_point_addition_random_points_0(void)
{
    JacobianPoint result_point;

    JacobianPoint point_a = {
        .x = {.limbs = {
                  0x7a7b5d43f0f262dd, 0x66ee6f83caa11e92, 0x27a6f97479d59039, 0x48f9bc76c49d7be8

              }},
        .y = {.limbs = {

                  0x0118dd38ab545cfe, 0x1df77f56040ab5fb, 0x6edf341b59a030a6, 0xa2055c8b6e6f718e

              }},
        .z = {.limbs = {

                  0x61438dec8103fdfb, 0xc103d3905b11c1f2, 0x8edee50c68a0dfc0, 0xfe50900b9f72c446

              }}};

    JacobianPoint point_b = {
        .x = {.limbs = {
                  0x03f1a14a95351710, 0x9874171985bf63f8, 0x619e79cbc7ece363, 0xcde3a96e1147ad45

              }},
        .y = {.limbs = {

                  0xe3cb2a8abf70d219, 0xcbc3c5ed45c12018, 0xee3d29f5bece0d8b, 0x21b838c47aec3131

              }},
        .z = {.limbs = {

                  0x81370d7c09f4f2f8, 0x7a46782913b0d920, 0xd7115e79348d3083, 0x1c53a72a89c09a6f

              }}};

    JacobianPoint expected_jacobian_point = {
        .x = {.limbs = {
                  0xbf4d6448385d3b03, 0xb2a71b0ab730264b, 0x0783f0a5378a8470, 0x1019191bd61d1e17

              }},
        .y = {.limbs = {

                  0xfb27ebca5d44bb3b, 0xeb3159c0e8134851, 0xaf51e7ffa7be7577, 0xe0e16434bf657df1

              }},

        .z = {.limbs = {

                  0x5d786e3e0df45c8a, 0xabbd346deb5249f0, 0x387d0304631efc11, 0x02dde22684762fb1

              }}};

    jacobian_point_addition(&point_a, &point_b, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_jacobian_point, result_point);
}

void test_jacobian_point_addition_random_points_1(void)
{
    JacobianPoint result_point;

    JacobianPoint point_a = {
        .x = {.limbs = {
                  0x34b403a0ae8978a2, 0x9ca1d6716b2b2270, 0x253c369ef61c5ee6, 0x0da4512d500dcbf7

              }},
        .y = {.limbs = {

                  0x1b6c88254aff0aad, 0xbe09dec8808cdfbb, 0x60632f0d45b6e731, 0x8e7b62f898d25784

              }},
        .z = {.limbs = {

                  0x6c47bd00fb3d784f, 0x3df2b4e97fc53860, 0x087b2291cc9caa5f, 0x81ecab0fd54ab169

              }}};

    JacobianPoint point_b = {
        .x = {.limbs = {
                  0xd32b9d1785f6f821, 0x42e528964d50a4a2, 0x51cb53428d3437b5, 0x140cb0371d4e0513

              }},
        .y = {.limbs = {

                  0x3defa102b532c045, 0xa8071d0a869e3e44, 0xe7a325f81753cc42, 0x00e0041b6d028c8e

              }},
        .z = {.limbs = {

                  0x5fc529ba4b205af7, 0x11146cc7449f9b6c, 0xddb1584b74bf0973, 0x4b54d15ac18d5804

              }}};

    JacobianPoint expected_jacobian_point = {
        .x = {.limbs = {
                  0x6ab23eb7d3526e9b, 0x6f117ee2ea821c90, 0x49490d4723944c0f, 0x6024312491caaa65

              }},
        .y = {.limbs = {

                  0x3a2f45a5e4566a0a, 0x5acd8e519c06d53b, 0x7b79c5fa54979d24, 0x0ecf125f64f46959

              }},

        .z = {.limbs = {

                  0xb9db4f5d3ca32cb4, 0x5da821844eecf3fe, 0x1899a1568d261151, 0xc140e37b70b37ea6

              }}};

    jacobian_point_addition(&point_a, &point_b, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_jacobian_point, result_point);
}

void test_jacobian_point_addition_random_points_2(void)
{
    JacobianPoint result_point;

    JacobianPoint point_a = {
        .x = {.limbs = {
                  0xc2baa4a4dc72fb5d, 0x59091bd93b5caaf9, 0x56d2b5f618727b13, 0x4148f6067c489e8e

              }},
        .y = {.limbs = {

                  0xd3d3946c04cd9def, 0x74dd022a7f5e72ed, 0x715379651646013c, 0x9d062c4110d03988

              }},
        .z = {.limbs = {

                  0xbcc4c06a32fac470, 0xe70ac39dad1be022, 0x1b79ea7adf17daad, 0xef5d438773ccbe8b

              }}};

    JacobianPoint point_b = {
        .x = {.limbs = {
                  0x160842ddcacadc98, 0x26f644ecf95bced2, 0xc2198d07a5bf277a, 0x8e05756e5ebbbd5d

              }},
        .y = {.limbs = {

                  0x6b72a1d567d53e95, 0x3c587626c2f14d63, 0xe3a0758cca2240ff, 0x2f3c167c9d606623

              }},
        .z = {.limbs = {

                  0xdc998a29d46dc750, 0x639680eec539fb9c, 0xe17d440b05a1ed84, 0xc6cb83cfcf3324fc

              }}};

    JacobianPoint expected_jacobian_point = {
        .x = {.limbs = {
                  0x7d75a0939988ed79, 0x860398981c98d587, 0x4f45361beae44b8c, 0x2f412469c8b9ac97

              }},
        .y = {.limbs = {

                  0x54df2f4a0c93a5e2, 0xb26a26764bd512f9, 0x95f3e17c242767f0, 0xc70906736b62c023

              }},

        .z = {.limbs = {

                  0xd6dff2837b306310, 0xfeba4379a956d485, 0xa8bbabf209ff51bd, 0x3cdf024f99a99162

              }}};

    jacobian_point_addition(&point_a, &point_b, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_jacobian_point, result_point);
}

void test_jacobian_point_addition_random_points_3(void)
{
    JacobianPoint result_point;

    JacobianPoint point_a = {
        .x = {.limbs = {
                  0x8a5781f93742bf5f, 0x0521378a2cb165c2, 0x682dfc44dea1830e, 0x84fa63a0f0bc008a

              }},
        .y = {.limbs = {

                  0xb3b6d5b8a43503bd, 0x4408c68e12a49c5f, 0x69c39c903eb6653f, 0x9f8dbf109be23504

              }},
        .z = {.limbs = {

                  0x0f82f697b60ebc8c, 0x09a4239fd63ecee5, 0xb46d58fdc9b92801, 0xc6fbb96aee970385

              }}};

    JacobianPoint point_b = {
        .x = {.limbs = {
                  0x079319d4fd24d4ce, 0xa53595ce8a3cdf07, 0x20ebe6b8afd36e09, 0x70e0abd8928f8d93

              }},
        .y = {.limbs = {

                  0x21c071dd277d2725, 0xf73b8d977b7cde75, 0x25c2884cb235e252, 0x40aec097ab9536cb}},
        .z = {.limbs = {

                  0x18d84aee5e2f5ac5, 0xe5313fda93f345ef, 0x8fe5a2a3cf97330d, 0xee3726f958e9661d

              }}};

    JacobianPoint expected_jacobian_point = {
        .x = {.limbs = {
                  0x3d1056bee5e39cbc, 0xd74b653267e0a66c, 0xec4edf003629a5ae, 0xfbf9687395c3b267

              }},
        .y = {.limbs = {

                  0x5fa64ee3c7ae8ef7, 0xb714100b2eeabf7c, 0x81b558b7cdb1e673, 0x357f11c0b5c39903

              }},

        .z = {.limbs = {

                  0xab81f9873128150f, 0x49e37fc2837d3e7d, 0xf1dade5f6ff21886, 0x31852045af0c4ca8

              }}};

    jacobian_point_addition(&point_a, &point_b, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_jacobian_point, result_point);
}

void test_jacobian_point_addition_random_points_4(void)
{
    JacobianPoint result_point;

    JacobianPoint point_a = {
        .x = {.limbs = {

                  0x815a4d99f2b5da1b, 0x6d45c862cefea23d, 0x605d3a50565a4706, 0xcdcac4af3fa943ab}},
        .y = {.limbs = {

                  0x448da9dbde7493b6, 0x9751a925a12b1773, 0x91cdfec65a196aa3, 0x13fc845c4bd0d179

              }},
        .z = {.limbs = {

                  0x908b5305b3c79947, 0x006b5f3495160d99, 0xc735bead6e53ff0c, 0x30f004905296392c

              }}};

    JacobianPoint point_b = {
        .x = {.limbs = {
                  0x43fff9ba75926477, 0xc5a2473719caafb0, 0x377bdc188192b9f4, 0xee24d2c24710288d

              }},
        .y = {.limbs = {

                  0xc5fbb3b77f38b343, 0x695362df72488eeb, 0x320471cf6e2de753, 0x66be85e1e0b4c313

              }},
        .z = {.limbs = {

                  0x354939dcb6abddde, 0x57f042c55d798f87, 0x5678a3573a5bd938, 0xaed5efc5a9e256a1

              }}};

    JacobianPoint expected_jacobian_point = {
        .x = {.limbs = {
                  0xa427a578e1c6f3b7, 0x5ab3d5ddfe3c7e1b, 0xac918d73b1dacdae, 0x1db7c7221a8549bc

              }},
        .y = {.limbs = {

                  0x2b0e888a8ac982ac, 0x9f72f7b6a6bff676, 0x391bca11745c91ac, 0x941cdde752ee7257

              }},

        .z = {.limbs = {

                  0x90355d375ff1e726, 0xd5e060f78b88cd13, 0x24df74ce9ce7b178, 0x7c031dd480ef34d3

              }}};

    jacobian_point_addition(&point_a, &point_b, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_jacobian_point, result_point);
}
