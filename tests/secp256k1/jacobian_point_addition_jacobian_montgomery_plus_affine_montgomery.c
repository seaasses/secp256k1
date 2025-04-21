#include "structs/point.h"
#include "unity/unity.h"
#include "constants/secp256k1.h"
#include "secp256k1/jacobian_point_addition_jacobian_montgomery_plus_affine_montgomery.h"

void test_jacobian_point_addition_jacobian_montgomery_plus_affine_montgomery_0(void)
{
    JacobianPoint result_point;

    JacobianPoint point_a = {
        .x = {.limbs = {
                  0x4ac1e1fa47d3824a, 0x3b21d6ced2eec0fc, 0x37e4f204c7bace28, 0xa061f1e7c842b041

              }},
        .y = {.limbs = {

                  0xad4738f2b6e39805, 0x1e2e583173c73a82, 0x6a098e4ef57bac88, 0x166ce801896611f7

              }},
        .z = {.limbs = {

                  0x91340693e6ed753a, 0x25c8680e46e3d9bf, 0x5cf7b6d3e0b7b86e, 0xe05ec4efe6cc6d9a

              }}};

    Point point_b = {
        .x = {.limbs = {
                  0x98e208b81f60dffb, 0x46bac3f785842f68, 0xd10a7b4d15f49210, 0xc23c0c2871dcfde5

              }},
        .y = {.limbs = {

                  0x373f61c8e68e4c5b, 0x08e6a45a8de84e95, 0x5506aa03cb7b7c40, 0xdf0ca650995c4bba

              }},
    };

    JacobianPoint expected_jacobian_point = {
        .x = {.limbs = {
                  0x2831fb505b1abbb4, 0x605c27e55c8cd243, 0x9828a3d1715b06bb, 0x4cf1a801bd444ab3

              }},
        .y = {.limbs = {

                  0xc7bfd648d9be3357, 0x0bf3443e2df47ecd, 0x017baa4c8cb1d55e, 0x047ca2e190844209

              }},

        .z = {.limbs = {

                  0x98b5da62dbcaf8f1, 0xd6af2c39ebb0cae0, 0x8c312cb4d1deeab0, 0xa9ba6bf0e051b276

              }}};

    jacobian_point_addition_jacobian_montgomery_plus_affine_montgomery(&point_a, &point_b, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_jacobian_point, result_point);
}
void test_jacobian_point_addition_jacobian_montgomery_plus_affine_montgomery_1(void)
{
    JacobianPoint result_point;

    JacobianPoint point_a = {
        .x = {.limbs = {
                  0x9cf7eca529d24a02, 0x1f675745ad0ea51d, 0x3fc9a1a843ccf4b3, 0x5ab34869923581bc

              }},
        .y = {.limbs = {

                  0xae4fa6f7c0a358d7, 0xc84d9c02744dfc8f, 0x76b6aa55b881fb69, 0x4fdfb196bff84c42

              }},
        .z = {.limbs = {

                  0xaaa6f5667258500e, 0x53d68b35c48d30e0, 0xf7ea128c47001c66, 0xd9670005122d6203

              }}};

    Point point_b = {
        .x = {.limbs = {
                  0xcebe22b39fdbef76, 0xe9b2cea8d30471c1, 0x0d5c76573531317c, 0x277425e39b440dd8

              }},
        .y = {.limbs = {

                  0x590d9a72429620cd, 0xca46bf2636edfb85, 0xff24a0aeb3de12d1, 0xe2a4b4b6d19acd1f

              }},
    };

    JacobianPoint expected_jacobian_point = {
        .x = {.limbs = {
                  0x06e0c21639ea673d, 0x7333c28512c844cd, 0x3332800099ceccf4, 0xc0baa504d8d02b45

              }},
        .y = {.limbs = {

                  0x4a5ccc1169e84ab5, 0xffa94b6569040223, 0xf5455a685aafb1b3, 0xb1212f062f03c73c

              }},

        .z = {.limbs = {

                  0xb2e95269d1a57982, 0xe89626ece84f437d, 0x1a544fddabb5c6a0, 0x7392362be1b58702

              }}};

    jacobian_point_addition_jacobian_montgomery_plus_affine_montgomery(&point_a, &point_b, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_jacobian_point, result_point);
}

void test_jacobian_point_addition_jacobian_montgomery_plus_affine_montgomery_2(void)
{
    JacobianPoint result_point;

    JacobianPoint point_a = {
        .x = {.limbs = {
                  0x7a1a322b2fff8218, 0x05e9b52d65278e90, 0x4cef27592395bd96, 0xdae6dda85139e4bc

              }},
        .y = {.limbs = {

                  0x67fb1c6de07d35ff, 0x82d1352c0253c23e, 0x373335f9bba4ab51, 0x101cc39193d7ea73

              }},
        .z = {.limbs = {

                  0xc3537a685bdbcde4, 0x62fdf9d7100cf056, 0x274df5b75cf35b93, 0xed927a989412c0f6

              }}};

    Point point_b = {
        .x = {.limbs = {
                  0x9719c5473e6c726f, 0xec108e34b22b10d6, 0x9ae8a34226f0e4b4, 0x32afed71cbcd2b26

              }},
        .y = {.limbs = {

                  0x40c4300b4fedeac2, 0xcf2d5319a031f8f6, 0x15f89814e5951224, 0x94a0e912cbaf8fc1

              }},
    };

    JacobianPoint expected_jacobian_point = {
        .x = {.limbs = {
                  0xdb5b03acbffaf0e0, 0x40d12f3c2f10d9b7, 0xeaa80af7301c5251, 0x9b78d98bea64454a

              }},
        .y = {.limbs = {

                  0x08ee19da1dde6e47, 0x7a189391f40189a2, 0x6777bdab796e9a3a, 0x7d00e1e2b7c3c43b

              }},

        .z = {.limbs = {

                  0x902f1ded7aad9892, 0x096fc7007a7ed877, 0x990007b187e34f5f, 0xe59d88d550bbb2b4

              }}};

    jacobian_point_addition_jacobian_montgomery_plus_affine_montgomery(&point_a, &point_b, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_jacobian_point, result_point);
}
void test_jacobian_point_addition_jacobian_montgomery_plus_affine_montgomery_3(void)
{
    JacobianPoint result_point;

    JacobianPoint point_a = {
        .x = {.limbs = {
                  0x07bb2fd20f41e5dd, 0x5c16c7d3b28843a1, 0x94eaba7a911fcd84, 0x7a544d95d905dd1e

              }},
        .y = {.limbs = {

                  0x7e4f6ea4bc3126da, 0x03e96d0707eb645a, 0x048ecd45e1061c48, 0x03200168d2fe2c4d

              }},
        .z = {.limbs = {

                  0x8ce6e8e733d5b8aa, 0xb8cbc12b987e30d4, 0x3d8a9dec11d27be0, 0xc07d63ef0d6c369a

              }}};

    Point point_b = {
        .x = {.limbs = {
                  0x49410e19ca2925dc, 0x569eecc817242917, 0xc9fbbcd6241f587d, 0xdf31976bcb71d6d8

              }},
        .y = {.limbs = {

                  0xf3d498e6215193a0, 0xe98b4a2878055fd1, 0xc12851c140ad00c1, 0x7aab4c8555be63bf

              }},
    };

    JacobianPoint expected_jacobian_point = {
        .x = {.limbs = {
                  0x7aa410755f019a77, 0xd45e3199797d10ab, 0xbe6f66109707cd7e, 0x2d3388b2f4cb4273

              }},
        .y = {.limbs = {

                  0xfe7ee2035578c5dd, 0x3708bf81bfeb22c6, 0x71d13cc37e81be2f, 0x3d8c55ebe3a50c34

              }},

        .z = {.limbs = {

                  0xf8adc9f8c7b14c9e, 0xb33af89d35547a4f, 0x136e839b7dc88c6a, 0x11775b04d371af13

              }}};

    jacobian_point_addition_jacobian_montgomery_plus_affine_montgomery(&point_a, &point_b, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_jacobian_point, result_point);
}
void test_jacobian_point_addition_jacobian_montgomery_plus_affine_montgomery_4(void)
{
    JacobianPoint result_point;

    JacobianPoint point_a = {
        .x = {.limbs = {
                  0x1d03a556271ec2bf, 0x6432f11026cf31e7, 0x7c259b21c61110c5, 0x160f953d173f0f64

              }},
        .y = {.limbs = {

                  0xfa0b72ca36a1d052, 0xae6109a6e57fe63b, 0x7b60fb6ee4623849, 0x7a345112eaeb1592

              }},
        .z = {.limbs = {

                  0xdf53a1129fd80678, 0x358bdb42e532cf42, 0xf1eb4cd4c4aa5b42, 0xbb4641d6af67ddf2

              }}};

    Point point_b = {
        .x = {.limbs = {
                  0xc0cc0aad28e9bd5a, 0xbc52e3055cf0f92c, 0x4889bc9ce055b8f8, 0x1e7db8ea643cac91

              }},
        .y = {.limbs = {

                  0x81a903fd9dda1710, 0xe4ab7e5cc049e96b, 0x38498a919002d9b1, 0x09f071529a1c748a

              }},
    };

    JacobianPoint expected_jacobian_point = {
        .x = {.limbs = {
                  0x7783fbce81dd03b8, 0x5f819e5654f9fa2f, 0xefc366f70214e6cb, 0xc13d60ebfc109cbb

              }},
        .y = {.limbs = {

                  0xcd48a039957668f4, 0x7835104a6d41ef4f, 0x0f270e8114af7011, 0xc9f5c128fe2bef9e

              }},

        .z = {.limbs = {

                  0xf487ff052c6076a5, 0xa03551cb43dc64bb, 0xb0e6c5735fa54d21, 0x4510ce5f036ff9c7

              }}};

    jacobian_point_addition_jacobian_montgomery_plus_affine_montgomery(&point_a, &point_b, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_jacobian_point, result_point);
}