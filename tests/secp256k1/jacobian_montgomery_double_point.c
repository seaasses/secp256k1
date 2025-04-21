#include "structs/point.h"
#include "unity/unity.h"
#include "secp256k1/jacobian_montgomery_double_point.h"

void test_jacobian_montgomery_double_point_random_point_0(void)
{
    JacobianPoint result_point;

    JacobianPoint point = {
        .x = {.limbs = {
                  0x10369facca0b1c9a, 0x76627a2697b5929f, 0x663bde225e85abe1, 0x1ecedf0421efb66e}},
        .y = {.limbs = {0x3e665cee95265d58, 0x3642c0fcdd6f797c, 0x0bc35a42232df54a, 0x17b476b7d70ee3a3}

        },
        .z = {.limbs = {0xd73d0c9cf5c2dc18, 0x0e5b0f99e007c13b, 0xd7bcff25592d36bb, 0x85997adcc93e7e60}}};

    JacobianPoint expected_result = {
        .x = {.limbs = {
                  0xbef1d1fffb7159c0, 0x2ddb5ae552311a70, 0xad6b667c839028bc, 0x6ed691986b71f862

              }},
        .y = {.limbs = {

                  0x63478f209643f028, 0x42c166a172517743, 0x3e3f59d0f792cfae, 0x0abc3cf435f1c717

              }},

        .z = {.limbs = {

                  0x8efa2798124e26e6, 0x5ab7bccfee039a6a, 0x31a93fac3569ee51, 0xf4e6e3a6f2498a08

              }}};

    jacobian_montgomery_double_point(&point, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_result, result_point);
}

void test_jacobian_montgomery_double_point_random_point_1(void)
{
    JacobianPoint result_point;

    JacobianPoint point = {
        .x = {.limbs = {
                  0xdcdfa1c68c1fbbac, 0x4bb33f805217b4e4, 0xb0d5debef058e26b, 0x94d8b11bcb03a8c4}},
        .y = {.limbs = {0x17656dccf757f634, 0x6cb0044be42a7278, 0x66086471e8ded81a, 0xac60ecf911e0379d}

        },
        .z = {.limbs = {0x3a1a0566eaf6e1ff, 0x187c5fecc93779e3, 0x2711aa3c164fc43a, 0x21a532ce3e7cab77}}};

    JacobianPoint expected_result = {
        .x = {.limbs = {
                  0x16132e74c7e650e3, 0xd79faed6b2cec907, 0xb6522830c5c19132, 0x1004c55580c92cc7

              }},
        .y = {.limbs = {

                  0x21cf4ef1da8bcae9, 0x303f582fe47ef6fb, 0xbbcde8d9d820e11f, 0x80b05ad19fd6c6b7

              }},

        .z = {.limbs = {

                  0xd9bcd6146b88f1ba, 0xd7666adfdb6ff8be, 0x4dd659a7e4f5a2fc, 0xe4c2a23ecd62ad33

              }}};

    jacobian_montgomery_double_point(&point, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_result, result_point);
}

void test_jacobian_montgomery_double_point_random_point_2(void)
{
    JacobianPoint result_point;

    JacobianPoint point = {
        .x = {.limbs = {
                  0xdac54172479c9bf4, 0x6c04d1a827ff6404, 0xaea645924c4ddc42, 0x133ed41273a5a773}},
        .y = {.limbs = {0xe2988a1c52262cd2, 0x9941a7fed876edec, 0xacdc7b741f5b96e2, 0x2a2029a151932b2e}

        },
        .z = {.limbs = {0x59da7e8309afa107, 0x6b369c1a298f19b7, 0x2104a6d1048372b8, 0xff08b320c70b2324}}};

    JacobianPoint expected_result = {
        .x = {.limbs = {
                  0x7457f0abe8b1a9f2, 0x61e5939f88cc5ca1, 0xd3b96bd11341135b, 0x22e6dcbe7b941063

              }},
        .y = {.limbs = {

                  0xaef95770595539d9, 0xb2860926361242ea, 0x1a7ccaf8d77a62f7, 0x50681b05139352c7

              }},

        .z = {.limbs = {

                  0x3b6d0eb6a89e767a, 0xe6232ca0da55a0c9, 0x90d4efe9a7e20a53, 0x5f37651aa91bf8a4

              }}};

    jacobian_montgomery_double_point(&point, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_result, result_point);
}

void test_jacobian_montgomery_double_point_random_point_3(void)
{
    JacobianPoint result_point;

    JacobianPoint point = {
        .x = {.limbs = {
                  0xa9843814cea08d6d, 0x7ecdaebeab8061ba, 0x7967f16920adc061, 0x818eacad73b56335}},
        .y = {.limbs = {0xd703355ecce30f30, 0xf06f26bc85122ab5, 0x1340908853b80aa7, 0x8312673577671011}

        },
        .z = {.limbs = {0x7487486248cc8787, 0x34eb41f48af77eed, 0xd8e5be39a8ec699a, 0xedb084f0e89e2dc7}}};

    JacobianPoint expected_result = {
        .x = {.limbs = {
                  0x042154ceb742b31f, 0xa89ca2cb16a8b7c9, 0x973bdb7c9345757e, 0x13b260ea9d3fef91

              }},
        .y = {.limbs = {

                  0x5cb1bf8196b84e12, 0x5bcb470aac38e283, 0x61135ef7cbb1e129, 0xdada97e1f8c515bb

              }},

        .z = {.limbs = {

                  0x18d7e06c739e76b6, 0x04534c80ba167fe4, 0x5abb8e7f22dd04e7, 0x10d1a63c28e3a251

              }}};

    jacobian_montgomery_double_point(&point, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_result, result_point);
}

void test_jacobian_montgomery_double_point_random_point_4(void)
{
    JacobianPoint result_point;

    JacobianPoint point = {
        .x = {.limbs = {
                  0x984abdeb2042d5e4, 0x30fc30d8d0429184, 0xc042327aa3474f8d, 0xb1c9ba0a340a28e7}},
        .y = {.limbs = {0x4f55b28e2c495201, 0xb8c69405120b31bc, 0xd3d76879db6a73eb, 0x043d1624b2681531}

        },
        .z = {.limbs = {0xccea86d08c804fc6, 0x2ab48e98e6609ea4, 0x16ba69799b143171, 0x343f39dd50790aa7}}};

    JacobianPoint expected_result = {
        .x = {.limbs = {
                  0x2b8ac2311b2323b4, 0x93689a9f358f4891, 0x69473e52e5d58862, 0x5a806bc9a169aa7d

              }},
        .y = {.limbs = {

                  0x843e85f7a5d2deb5, 0xb2e1d627983ccb5a, 0xcdf2623b3b141c9d, 0x1064675f60257b2e

              }},

        .z = {.limbs = {

                  0xead521218ad1791b, 0xc3359db2119b2ea2, 0xfeb4c53f73d07937, 0xfd6828eae07d21d6

              }}};

    jacobian_montgomery_double_point(&point, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_result, result_point);
}
