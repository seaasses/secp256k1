#include "structs/point.h"
#include "unity/unity.h"
#include "secp256k1/jacobian_double_point.h"

void test_jacobian_double_point_random_point_0(void)
{
    JacobianPoint result_point;

    JacobianPoint point = {
        .x = {.limbs = {
                  0x74a85623487fa764, 0xcecf2961fcb0257b, 0xe73e1a52e51335d3, 0x12e6a7039f8acda1}},
        .y = {.limbs = {0x24aa17af4fb4acd7, 0x460c1058d975f427, 0x2a2596870f98b50c, 0xdb45ad5024c26723}

        },
        .z = {.limbs = {0xc51c624b400edc9b, 0xe00a5991fed7c88b, 0x7f6b6c84d3d12e90, 0x770a3686a82fb05d}}};

    JacobianPoint expected_result = {
        .x = {.limbs = {
                  0x481cf2c63e4cc0e7, 0x7df73380bb45852c, 0x817781e84b10809a, 0x5e19d1150ca58cfc

              }},
        .y = {.limbs = {

                  0x00d95bb191be9d6f, 0x10b91b8eb2cc2139, 0xe51d667620ede750, 0x954c0ec15ce6a143

              }},

        .z = {.limbs = {

                  0xdadd6ff6a443adc3, 0x8e2604446eac1827, 0x00dafafb7f866ed7, 0xebfd3a80a56dc9ba

              }}};

    jacobian_double_point(&point, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_result, result_point);
}

void test_jacobian_double_point_random_point_1(void)
{
    JacobianPoint result_point;

    JacobianPoint point = {
        .x = {.limbs = {
                  0x79c4c5d6d2868bae, 0xec90c0cf7a8028c2, 0x88ed339d41a408fd, 0xdfe509538091b9a8}},
        .y = {.limbs = {0xffd0db0fbe2e09f5, 0x328b4e77468f61c2, 0x093ad2cc0b3dc584, 0x6c60629dbb602eec}

        },
        .z = {.limbs = {0xe490be34048ebeff, 0xded5e970f9d4362b, 0xfeacbddb8cd4a159, 0x1b54b36b288e65e9}}};

    JacobianPoint expected_result = {
        .x = {.limbs = {
                  0xcdb6e1d0a9c7eb41, 0x142bd35cbb83f5d6, 0x215003ab61c12cf8, 0xf5d3b2bd5c65dd97

              }},
        .y = {.limbs = {

                  0x71ca72d1d63e7735, 0xe4eb959611a4de2d, 0x5bb319384388d7b2, 0xfdf1da8f96a15f65

              }},

        .z = {.limbs = {

                  0x6de98bb728eb14c5, 0x31a7b4c7cd08a5a8, 0xa6eb8aec54f160d2, 0x83c25b3bae7f332d

              }}};

    jacobian_double_point(&point, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_result, result_point);
}

void test_jacobian_double_point_random_point_2(void)
{
    JacobianPoint result_point;

    JacobianPoint point = {
        .x = {.limbs = {
                  0x6834db3d47d0c726, 0xfc54914d43d90212, 0x80cadccd2e66b510, 0xa39782179670fa3b}},
        .y = {.limbs = {0xd818b1b2a33380ae, 0xb5098b8595754e0e, 0x61a0065e83a68e6c, 0xb9b52717672c1f9c}

        },
        .z = {.limbs = {0x9f95a070b83eba69, 0x0bd8fab553bc15fd, 0x04792108ffb6db81, 0xed0dd347af49e672}}};

    JacobianPoint expected_result = {
        .x = {.limbs = {
                  0xaad34b765f3f391b, 0x5d9d12c36bb4c440, 0x1edb7ada331afc07, 0x28bbb42f7d8abab3

              }},
        .y = {.limbs = {

                  0x799ad9618cfd0825, 0x43d3aaec7501a08c, 0x642e12a9e214032e, 0x3df96b8dc7fa3374

              }},

        .z = {.limbs = {

                  0xcb5eef90b4e0397b, 0xe490a1bb21186561, 0x5e049d1ce48d1643, 0x3c12605d012fe2c8

              }}};

    jacobian_double_point(&point, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_result, result_point);
}
void test_jacobian_double_point_random_point_3(void)
{
    JacobianPoint result_point;

    JacobianPoint point = {
        .x = {.limbs = {
                  0x76d75561b21657a6, 0x9f9cf7e0d23fabf2, 0x9b2b04b5e0907fe8, 0x6b8f914cde567dd5}},
        .y = {.limbs = {0x22262c44593a3fcb, 0xd612976716cf7884, 0x2ecfa958c3c70fe3, 0x7330a7d4ece7b7fa}

        },
        .z = {.limbs = {0x0feeb5316d3cf613, 0x4a8314dac4a7f37c, 0xf12fcacbc810b712, 0x801c19076100a1d9}}};

    JacobianPoint expected_result = {
        .x = {.limbs = {
                  0x2e38d8951993bf0e, 0x8ccef3d92e303878, 0xd7d922661e8e30b7, 0x8fd7d6df0ffd82bf

              }},
        .y = {.limbs = {

                  0x5d5c194b67a4a5d8, 0x5729ca937d36e6ee, 0x22e1760d3ca375f5, 0x754cf2f2fa0a86ca

              }},

        .z = {.limbs = {

                  0xeebd0c286df572b1, 0x8dfba5e943ccf413, 0x820f243d12f0566f, 0xa4fe37464747af17

              }}};

    jacobian_double_point(&point, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_result, result_point);
}

void test_jacobian_double_point_random_point_4(void)
{
    JacobianPoint result_point;

    JacobianPoint point = {
        .x = {.limbs = {
                  0x9549e1427aa5c057, 0x30396aa9180c6baa, 0x8533ffbdc17ddcdf, 0xa0a991477de8e68d}},
        .y = {.limbs = {0xfad7942359c2b35a, 0xa59147f3ec731269, 0xeb4543402869d93f, 0xd7efd1ae17958446}

        },
        .z = {.limbs = {0x181215618e7cbb9b, 0xaa4ad7aa3b6e8503, 0x54cd7a9bdf7ed412, 0x55feaadbd4da3ea2}}};

    JacobianPoint expected_result = {
        .x = {.limbs = {
                  0x1931d381d2812599, 0xc21b237341b56b1d, 0x619ac1ddd0c2cfb1, 0x4b11484aac913461

              }},
        .y = {.limbs = {

                  0x1127c4b00c645c25, 0x29dbe1f137cd1652, 0xdbf871c78fa4a441, 0x2ae3ef670e704506

              }},

        .z = {.limbs = {

                  0xad2605aada4b1aeb, 0xdd0a2797f7839060, 0xa8b93a74798f55a5, 0x55337f8cd4ed6ec8

              }}};

    jacobian_double_point(&point, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_result, result_point);
}

void test_jacobian_double_point_random_point_5(void)
{
    JacobianPoint result_point;

    JacobianPoint point = {
        .x = {.limbs = {
                  0xb6d61a54316eb15a, 0x6b1bd740006a9513, 0x4403b5715050c99a, 0x2770950da11b134d}},
        .y = {.limbs = {0x2cc4496b8506e5a2, 0x9771cb7af31991e3, 0x8334a7db23ac242b, 0x33e56e60d192dfbc}

        },
        .z = {.limbs = {0x45c2f7bd20863393, 0xd08897d946daa64e, 0x7fb3074b252734ea, 0x5b605301f86bcdd1}}};

    JacobianPoint expected_result = {
        .x = {.limbs = {
                  0x7444a87b9a1e3e0d, 0x2fe317f599363f33, 0xf2e317d041bedfe8, 0x015cbb1b542bd401

              }},
        .y = {.limbs = {

                  0xad843c2fec94cb4c, 0xcad7a65b8b82640e, 0x723e201ff37c0cc5, 0x195ddcd09ec229c7

              }},

        .z = {.limbs = {

                  0x32d3c8a70f2f05bc, 0xb481ec78b5314887, 0xfe1b4887f87f3a36, 0x3f7ae5e046ae00b0

              }}};

    jacobian_double_point(&point, &result_point);

    ASSERT_JACOBIAN_POINT_EQUAL(expected_result, result_point);
}