#include "constants/secp256k1.h"
#include "constants/montgomery.h"
#include "secp256k1/g_times_scalar.h"
#include "secp256k1/jacobian_montgomery_double_point.h"
#include "secp256k1/jacobian_double_point.h"
#include "secp256k1/jacobian_point_addition_jacobian_montgomery_plus_affine_montgomery.h"
#include "secp256k1/jacobian_point_affine_point_addition.h"
#include "secp256k1/jacobian_montgomery_to_affine.h"
#include "secp256k1/jacobian_to_affine.h"
#include <stdio.h>
inline void g_times_scalar_novo(const Uint256 *scalar, Point *result_point)
{

    // TODO: see better place for this
    static const Point g_times[256] = {
        {.x = {.limbs = {0, 0, 0, 0}}, .y = {.limbs = {0, 0, 0, 0}}}, // will never be used
        {.x = {.limbs = {0x79be667ef9dcbbac, 0x55a06295ce870b07, 0x029bfcdb2dce28d9, 0x59f2815b16f81798}}, .y = {.limbs = {0x483ada7726a3c465, 0x5da4fbfc0e1108a8, 0xfd17b448a6855419, 0x9c47d08ffb10d4b8}}},
        {.x = {.limbs = {0xc6047f9441ed7d6d, 0x3045406e95c07cd8, 0x5c778e4b8cef3ca7, 0xabac09b95c709ee5}}, .y = {.limbs = {0x1ae168fea63dc339, 0xa3c58419466ceaee, 0xf7f632653266d0e1, 0x236431a950cfe52a}}},
        {.x = {.limbs = {0xf9308a019258c310, 0x49344f85f89d5229, 0xb531c845836f99b0, 0x8601f113bce036f9}}, .y = {.limbs = {0x388f7b0f632de814, 0x0fe337e62a37f356, 0x6500a99934c2231b, 0x6cb9fd7584b8e672}}},
        {.x = {.limbs = {0xe493dbf1c10d80f3, 0x581e4904930b1404, 0xcc6c13900ee07584, 0x74fa94abe8c4cd13}}, .y = {.limbs = {0x51ed993ea0d455b7, 0x5642e2098ea51448, 0xd967ae33bfbdfe40, 0xcfe97bdc47739922}}},
        {.x = {.limbs = {0x2f8bde4d1a072093, 0x55b4a7250a5c5128, 0xe88b84bddc619ab7, 0xcba8d569b240efe4}}, .y = {.limbs = {0xd8ac222636e5e3d6, 0xd4dba9dda6c9c426, 0xf788271bab0d6840, 0xdca87d3aa6ac62d6}}},
        {.x = {.limbs = {0xfff97bd5755eeea4, 0x20453a14355235d3, 0x82f6472f8568a18b, 0x2f057a1460297556}}, .y = {.limbs = {0xae12777aacfbb620, 0xf3be96017f45c560, 0xde80f0f6518fe4a0, 0x3c870c36b075f297}}},
        {.x = {.limbs = {0x5cbdf0646e5db4ea, 0xa398f365f2ea7a0e, 0x3d419b7e0330e39c, 0xe92bddedcac4f9bc}}, .y = {.limbs = {0x6aebca40ba255960, 0xa3178d6d861a54db, 0xa813d0b813fde7b5, 0xa5082628087264da}}},
        {.x = {.limbs = {0x2f01e5e15cca351d, 0xaff3843fb70f3c2f, 0x0a1bdd05e5af888a, 0x67784ef3e10a2a01}}, .y = {.limbs = {0x5c4da8a741539949, 0x293d082a132d13b4, 0xc2e213d6ba5b7617, 0xb5da2cb76cbde904}}},
        {.x = {.limbs = {0xacd484e2f0c7f653, 0x09ad178a9f559abd, 0xe09796974c57e714, 0xc35f110dfc27ccbe}}, .y = {.limbs = {0xcc338921b0a7d9fd, 0x64380971763b61e9, 0xadd888a4375f8e0f, 0x05cc262ac64f9c37}}},
        {.x = {.limbs = {0xa0434d9e47f3c862, 0x35477c7b1ae6ae5d, 0x3442d49b1943c2b7, 0x52a68e2a47e247c7}}, .y = {.limbs = {0x893aba425419bc27, 0xa3b6c7e693a24c69, 0x6f794c2ed877a159, 0x3cbee53b037368d7}}},
        {.x = {.limbs = {0x774ae7f858a9411e, 0x5ef4246b70c65aac, 0x5649980be5c17891, 0xbbec17895da008cb}}, .y = {.limbs = {0xd984a032eb6b5e19, 0x0243dd56d7b7b365, 0x372db1e2dff9d6a8, 0x301d74c9c953c61b}}},
        {.x = {.limbs = {0xd01115d548e7561b, 0x15c38f004d734633, 0x687cf4419620095b, 0xc5b0f47070afe85a}}, .y = {.limbs = {0xa9f34ffdc815e0d7, 0xa8b64537e17bd815, 0x79238c5dd9a86d52, 0x6b051b13f4062327}}},
        {.x = {.limbs = {0xf28773c2d975288b, 0xc7d1d205c3748651, 0xb075fbc6610e58cd, 0xdeeddf8f19405aa8}}, .y = {.limbs = {0x0ab0902e8d880a89, 0x758212eb65cdaf47, 0x3a1a06da521fa91f, 0x29b5cb52db03ed81}}},
        {.x = {.limbs = {0x499fdf9e895e719c, 0xfd64e67f07d38e32, 0x26aa7b63678949e6, 0xe49b241a60e823e4}}, .y = {.limbs = {0xcac2f6c4b54e8551, 0x90f044e4a7b3d464, 0x464279c27a3f95bc, 0xc65f40d403a13f5b}}},
        {.x = {.limbs = {0xd7924d4f7d43ea96, 0x5a465ae3095ff411, 0x31e5946f3c85f79e, 0x44adbcf8e27e080e}}, .y = {.limbs = {0x581e2872a86c72a6, 0x83842ec228cc6def, 0xea40af2bd896d3a5, 0xc504dc9ff6a26b58}}},
        {.x = {.limbs = {0xe60fce93b59e9ec5, 0x3011aabc21c23e97, 0xb2a31369b87a5ae9, 0xc44ee89e2a6dec0a}}, .y = {.limbs = {0xf7e3507399e59592, 0x9db99f34f5793710, 0x1296891e44d23f0b, 0xe1f32cce69616821}}},
        {.x = {.limbs = {0xdefdea4cdb677750, 0xa420fee807eacf21, 0xeb9898ae79b97687, 0x66e4faa04a2d4a34}}, .y = {.limbs = {0x4211ab0694635168, 0xe997b0ead2a93dae, 0xced1f4a04a95c0f6, 0xcfb199f69e56eb77}}},
        {.x = {.limbs = {0x5601570cb47f238d, 0x2b0286db4a990fa0, 0xf3ba28d1a319f5e7, 0xcf55c2a2444da7cc}}, .y = {.limbs = {0xc136c1dc0cbeb930, 0xe9e298043589351d, 0x81d8e0bc736ae2a1, 0xf5192e5e8b061d58}}},
        {.x = {.limbs = {0x2b4ea0a797a443d2, 0x93ef5cff444f4979, 0xf06acfebd7e86d27, 0x7475656138385b6c}}, .y = {.limbs = {0x85e89bc037945d93, 0xb343083b5a1c8613, 0x1a01f60c50269763, 0xb570c854e5c09b7a}}},
        {.x = {.limbs = {0x4ce119c96e2fa357, 0x200b559b2f7dd5a5, 0xf02d5290aff74b03, 0xf3e471b273211c97}}, .y = {.limbs = {0x12ba26dcb10ec162, 0x5da61fa10a844c67, 0x6162948271d96967, 0x450288ee9233dc3a}}},
        {.x = {.limbs = {0x352bbf4a4cdd1256, 0x4f93fa332ce33330, 0x1d9ad40271f81071, 0x81340aef25be59d5}}, .y = {.limbs = {0x321eb4075348f534, 0xd59c18259dda3e1f, 0x4a1b3b2e71b1039c, 0x67bd3d8bcf81998c}}},
        {.x = {.limbs = {0x421f5fc9a2106544, 0x5c96fdb91c0c1e2f, 0x2431741c72713b4b, 0x99ddcb316f31e9fc}}, .y = {.limbs = {0x2b90f16d11dabdb6, 0x16f6db7e225d1e14, 0x743034b37b223115, 0xdb20717ad1cd6781}}},
        {.x = {.limbs = {0x2fa2104d6b38d11b, 0x0230010559879124, 0xe42ab8dfeff5ff29, 0xdc9cdadd4ecacc3f}}, .y = {.limbs = {0x02de1068295dd865, 0xb64569335bd5dd80, 0x181d70ecfc882648, 0x423ba76b532b7d67}}},
        {.x = {.limbs = {0xfe72c435413d33d4, 0x8ac09c9161ba8b09, 0x683215439d62b794, 0x0502bda8b202e6ce}}, .y = {.limbs = {0x6851de067ff24a68, 0xd3ab47e09d729981, 0x01dc88e36b4a9d22, 0x978ed2fbcf58c5bf}}},
        {.x = {.limbs = {0x9248279b09b4d68d, 0xab21a9b066edda83, 0x263c3d84e09572e2, 0x69ca0cd7f5453714}}, .y = {.limbs = {0x73016f7bf234aade, 0x5d1aa71bdea2b1ff, 0x3fc0de2a887912ff, 0xe54a32ce97cb3402}}},
        {.x = {.limbs = {0x6687cdb5b650d558, 0xf40cbdefc8e40997, 0xc03fe1b2abb84088, 0x5e5cad81710c4c8a}}, .y = {.limbs = {0x3fd502b3111178b1, 0x1a1fa873825c7200, 0x0ef8e529f033f272, 0xb32e83b25c83ad64}}},
        {.x = {.limbs = {0xdaed4f2be3a8bf27, 0x8e70132fb0beb752, 0x2f570e144bf615c0, 0x7e996d443dee8729}}, .y = {.limbs = {0xa69dce4a7d6c98e8, 0xd4a1aca87ef8d700, 0x3f83c230f3afa726, 0xab40e52290be1c55}}},
        {.x = {.limbs = {0x55eb67d7b7238a70, 0xa7fa6f64d5dc3c82, 0x6b31536da6eb344d, 0xc39a66f904f97968}}, .y = {.limbs = {0x7d916a47b2b58140, 0x0b1e718bf4042585, 0x40973bce1c95052d, 0xd0689f2f493be3c8}}},
        {.x = {.limbs = {0xc44d12c7065d812e, 0x8acf28d7cbb19f90, 0x11ecd9e9fdf281b0, 0xe6a3b5e87d22e7db}}, .y = {.limbs = {0x2119a460ce326cdc, 0x76c45926c982fdac, 0x0e106e861edf61c5, 0xa039063f0e0e6482}}},
        {.x = {.limbs = {0x6d2b085e9e382ed1, 0x0b69fc311a03f864, 0x1ccfff21574de092, 0x7513a49d9a688a00}}, .y = {.limbs = {0xacb82eb93309ad1c, 0xc739ddfa33604a83, 0x776238aa0bd5ff24, 0x8dbac47a17f388fb}}},
        {.x = {.limbs = {0x6a245bf6dc698504, 0xc89a20cfded60853, 0x152b695336c28063, 0xb61c65cbd269e6b4}}, .y = {.limbs = {0xe022cf42c2bd4a70, 0x8b3f5126f16a24ad, 0x8b33ba48d0423b6e, 0xfd5e6348100d8a82}}},
        {.x = {.limbs = {0xd30199d74fb5a22d, 0x47b6e054e2f378ce, 0xdacffcb89904a61d, 0x75d0dbd407143e65}}, .y = {.limbs = {0x95038d9d0ae3d5c3, 0xb3d6dec9e9838065, 0x1f760cc364ed8196, 0x05b3ff1f24106ab9}}},
        {.x = {.limbs = {0x1697ffa6fd9de627, 0xc077e3d2fe541084, 0xce13300b0bec1146, 0xf95ae57f0d0bd6a5}}, .y = {.limbs = {0xb9c398f186806f5d, 0x27561506e4557433, 0xa2cf15009e498ae7, 0xadee9d63d01b2396}}},
        {.x = {.limbs = {0x1be68a5a028f2601, 0xd0e80d468c344ba3, 0x31d611b96c358b60, 0x32e8b4da0547fc11}}, .y = {.limbs = {0xbebc47511ade7308, 0xb3ca6265f9400779, 0xc076329c75146bc6, 0xff1822f5d1f30e79}}},
        {.x = {.limbs = {0x605bdb019981718b, 0x986d0f07e834cb0d, 0x9deb8360ffb7f61d, 0xf982345ef27a7479}}, .y = {.limbs = {0x02972d2de4f8d206, 0x81a78d93ec96fe23, 0xc26bfae84fb14db4, 0x3b01e1e9056b8c49}}},
        {.x = {.limbs = {0xe0392cfa338aaf2f, 0x0b56c563e3e5e67a, 0x5d5fefe3388f85d9, 0x0c899da20f0198f9}}, .y = {.limbs = {0x76d458642a2c93ad, 0xee7a347a5e4681f9, 0xbb5b10f4bd8aa51e, 0xdfd6e3f50e7da3ac}}},
        {.x = {.limbs = {0x62d14dab4150bf49, 0x7402fdc45a215e10, 0xdcb01c354959b10c, 0xfe31c7e9d87ff33d}}, .y = {.limbs = {0x80fc06bd8cc5b010, 0x98088a1950eed0db, 0x01aa132967ab4722, 0x35f5642483b25eaf}}},
        {.x = {.limbs = {0xb699a30e6e184cdf, 0xa88ac16c7d80bffd, 0x38e2e1fc705821ea, 0x69cd5fdf1691fff7}}, .y = {.limbs = {0xd505700c51d860ce, 0x5a096ee637ebed3b, 0xd9d7268126c76a16, 0xb745bc318a51ab04}}},
        {.x = {.limbs = {0x80c60ad0040f27da, 0xde5b4b06c408e56b, 0x2c50e9f56b9b8b42, 0x5e555c2f86308b6f}}, .y = {.limbs = {0x1c38303f1cc5c30f, 0x26e66bad7fe72f70, 0xa65eed4cbe7024eb, 0x1aa01f56430bd57a}}},
        {.x = {.limbs = {0x91de2f6bb67b1113, 0x9f0e21203041bf08, 0x0eacf59a33d99cd9, 0xf1929141bb0b4d0b}}, .y = {.limbs = {0xeb9ef6c031eed31d, 0xe34e7a1009f87251, 0x55b03158202a9d3e, 0x9a9a2e83124a7899}}},
        {.x = {.limbs = {0x7a9375ad6167ad54, 0xaa74c6348cc54d34, 0x4cc5dc9487d84704, 0x9d5eabb0fa03c8fb}}, .y = {.limbs = {0x0d0e3fa9eca87269, 0x09559e0d79269046, 0xbdc59ea10c70ce2b, 0x02d499ec224dc7f7}}},
        {.x = {.limbs = {0xfe8d1eb1bcb3432b, 0x1db5833ff5f2226d, 0x9cb5e65cee430558, 0xc18ed3a3c86ce1af}}, .y = {.limbs = {0x07b158f244cd0de2, 0x134ac7c1d371cffb, 0xfae4db40801a2572, 0xe531c573cda9b5b4}}},
        {.x = {.limbs = {0xd528ecd9b696b54c, 0x907a9ed045447a79, 0xbb408ec39b68df50, 0x4bb51f459bc3ffc9}}, .y = {.limbs = {0xeecf41253136e5f9, 0x9966f21881fd656e, 0xbc4345405c520dbc, 0x063465b521409933}}},
        {.x = {.limbs = {0x5d045857332d5b9e, 0x541514731622af8d, 0x60c180165d971a61, 0xe06b70a9b3834765}}, .y = {.limbs = {0xdb2ba972802d45fd, 0x2decbab8d098a8c2, 0xa1d1f34761c6cf26, 0x1879a7cabf06fb68}}},
        {.x = {.limbs = {0x049370a4b5f43412, 0xea25f514e8ecdad0, 0x5266115e4a7ecb13, 0x87231808f8b45963}}, .y = {.limbs = {0x758f3f41afd6ed42, 0x8b3081b0512fd62a, 0x54c3f3afbb5b6764, 0xb653052a12949c9a}}},
        {.x = {.limbs = {0xf8b0b03d44112259, 0xf903b3d100e3950d, 0x980fdde9c7e85701, 0xc16baedc90235717}}, .y = {.limbs = {0xbd8e9dc301d9adc9, 0x6be1883b362f123b, 0xd0a986928ac79972, 0x517ab5c246242203}}},
        {.x = {.limbs = {0x77f230936ee88cbb, 0xd73df930d64702ef, 0x881d811e0e1498e2, 0xf1c13eb1fc345d74}}, .y = {.limbs = {0x958ef42a7886b640, 0x0a08266e9ba1b378, 0x96c95330d97077cb, 0xbe8eb3c7671c60d6}}},
        {.x = {.limbs = {0x6eca335d9645307d, 0xb441656ef4e65b4b, 0xfc579b27452bebc1, 0x9bd870aa1118e5c3}}, .y = {.limbs = {0xd50123b57a7a0710, 0x592f579074b875a0, 0x3a496a3a3bf8ec34, 0x498a2f7805a08668}}},
        {.x = {.limbs = {0xf2dac991cc4ce4b9, 0xea44887e5c7c0bce, 0x58c80074ab9d4dba, 0xeb28531b7739f530}}, .y = {.limbs = {0xe0dedc9b3b2f8dad, 0x4da1f32dec2531df, 0x9eb5fbeb0598e4fd, 0x1a117dba703a3c37}}},
        {.x = {.limbs = {0x29757774cc6f3be1, 0xd5f1774aefa8f02e, 0x50bc64404230e7a6, 0x7e8fde79bd559a9a}}, .y = {.limbs = {0xc39d07337ddc9268, 0xa0eba45a7a41876d, 0x151b423eac4033b5, 0x50bd28c17c470134}}},
        {.x = {.limbs = {0x463b3d9f662621fb, 0x1b4be8fbbe252012, 0x5a216cdfc9dae3de, 0xbcba4850c690d45b}}, .y = {.limbs = {0x5ed430d78c296c35, 0x43114306dd8622d7, 0xc622e27c970a1de3, 0x1cb377b01af7307e}}},
        {.x = {.limbs = {0x2b22efda32491a9e, 0x0294339ca3da761f, 0x7d36cfc8814c1b29, 0xca731921025ff695}}, .y = {.limbs = {0x7ed520327080a9fa, 0x4c16662fc134fadc, 0xc7048846d46ade00, 0x30b83fd19adc87cd}}},
        {.x = {.limbs = {0xf16f804244e46e2a, 0x09232d4aff3b5997, 0x6b98fac14328a2d1, 0xa32496b49998f247}}, .y = {.limbs = {0xcedabd9b82203f7e, 0x13d206fcdf4e33d9, 0x2a6c53c26e5cce26, 0xd6579962c4e31df6}}},
        {.x = {.limbs = {0x4fdcb8fa639cee44, 0x1c8331fd47a2e5ff, 0x3447be24500ca7a5, 0x249971067c1d506b}}, .y = {.limbs = {0x25a5208b674bfd4c, 0xae4d91eb555010aa, 0x422cc82409d50796, 0x90f3743d00fdaefb}}},
        {.x = {.limbs = {0xcaf754272dc84563, 0xb0352b7a14311af5, 0x5d245315ace27c65, 0x369e15f7151d41d1}}, .y = {.limbs = {0xcb474660ef35f5f2, 0xa41b643fa5e46057, 0x5f4fa9b7962232a5, 0xc32f908318a04476}}},
        {.x = {.limbs = {0xbce74de6d5f98dc0, 0x27740c2bbff05b6a, 0xafe5fd8d103f827e, 0x48894a2bd3460117}}, .y = {.limbs = {0x5bea1fa17a41b115, 0x525a3e7dbf0d8d5a, 0x4f7ce5c6fc73a6f4, 0xf216512417c9f6b4}}},
        {.x = {.limbs = {0x2600ca4b282cb986, 0xf85d0f1709979d8b, 0x44a09c07cb86d7c1, 0x24497bc86f082120}}, .y = {.limbs = {0x4119b88753c15bd6, 0xa693b03fcddbb45d, 0x5ac6be74ab5f0ef4, 0x4b0be9475a7e4b40}}},
        {.x = {.limbs = {0x45562f033698faca, 0x1540cbc9bf962cf4, 0x764c1ef4094ee4b6, 0x742b761c49b46d3b}}, .y = {.limbs = {0x9403d11a2b419eda, 0xacf931bfbd9c32a2, 0x64558508362bc5fc, 0x99025ec62b034e02}}},
        {.x = {.limbs = {0x7635ca72d7e8432c, 0x338ec53cd12220bc, 0x01c48685e24f7dc8, 0xc602a7746998e435}}, .y = {.limbs = {0x091b649609489d61, 0x3d1d5e590f78e6d7, 0x4ecfc061d57048ba, 0xd9e76f302c5b9c61}}},
        {.x = {.limbs = {0x01257e93a78a5b7d, 0x8fe0cf28ff1d8822, 0x350c778ac8a30e57, 0xd2acfc4d5fb8c192}}, .y = {.limbs = {0x1124ec11c77d356e, 0x042dad154e1116ed, 0xa7cc69244f295166, 0xb54e3d341904a1a7}}},
        {.x = {.limbs = {0x754e3239f325570c, 0xdbbf4a87deee8a66, 0xb7f2b33479d468fb, 0xc1a50743bf56cc18}}, .y = {.limbs = {0x0673fb86e5bda30f, 0xb3cd0ed304ea49a0, 0x23ee33d0197a695d, 0x0c5d98093c536683}}},
        {.x = {.limbs = {0x108443b948d15535, 0x84a271333f7fbd04, 0x3c4d66a91706edec, 0xbf07f6894c04f299}}, .y = {.limbs = {0x4e7b5daba34fbcf9, 0xf055520d4db8c49f, 0xd60282d32adfca55, 0x5b04403db9581a9f}}},
        {.x = {.limbs = {0xe3e6bd1071a1e96a, 0xff57859c82d570f0, 0x330800661d1c952f, 0x9fe2694691d9b9e8}}, .y = {.limbs = {0x59c9e0bba394e76f, 0x40c0aa58379a3cb6, 0xa5a2283993e90c41, 0x67002af4920e37f5}}},
        {.x = {.limbs = {0xbf23c1542d16eab7, 0x0b1051eaf832823c, 0xfc4c6f1dcdbafd81, 0xe37918e6f874ef8b}}, .y = {.limbs = {0x5cb3866fc3300373, 0x7ad928a0ba5392e4, 0xc522fc54811e2f78, 0x4dc37efe66831d9f}}},
        {.x = {.limbs = {0x186b483d056a0338, 0x26ae73d88f732985, 0xc4ccb1f32ba35f4b, 0x4cc47fdcf04aa6eb}}, .y = {.limbs = {0x3b952d32c67cf77e, 0x2e17446e204180ab, 0x21fb8090895138b4, 0xa4a797f86e80888b}}},
        {.x = {.limbs = {0x079264c4b4bfcd7f, 0xe3a7b7b92b6c439f, 0x3a5b3abcd29189bf, 0x7b54d781ff03d722}}, .y = {.limbs = {0x6f6f0e0784eada9f, 0x92999ee9c438d47e, 0xaa2c8068f1845197, 0xe3071c74b063c5e1}}},
        {.x = {.limbs = {0xdf9d70a6b9876ce5, 0x44c98561f4be4f72, 0x5442e6d2b737d9c9, 0x1a8321724ce0963f}}, .y = {.limbs = {0x55eb2dafd84d6ccd, 0x5f862b785dc39d4a, 0xb157222720ef9da2, 0x17b8c45cf2ba2417}}},
        {.x = {.limbs = {0x70e6b44a2ac6083a, 0xb673bacb5cb7ca55, 0x4b795b416e702c1c, 0x980bb7b87c78b8e9}}, .y = {.limbs = {0x49ba3203048e06d8, 0x4173867ab5324be4, 0x0a0d0e6436da1675, 0x4ff98b2aae170cf8}}},
        {.x = {.limbs = {0x5edd5cc23c51e87a, 0x497ca815d5dce0f8, 0xab52554f849ed899, 0x5de64c5f34ce7143}}, .y = {.limbs = {0xefae9c8dbc141306, 0x61e8cec030c89ad0, 0xc13c66c0d17a2905, 0xcdc706ab7399a868}}},
        {.x = {.limbs = {0xc00be8830995d1e4, 0x4f1420dd3b90d344, 0x1fb66f6861c84a35, 0xf959c495a3be5440}}, .y = {.limbs = {0xecf9665e6eba4572, 0x0de652a340600c73, 0x56efe24d228bfe6e, 0xa2043e7791c51bb7}}},
        {.x = {.limbs = {0x290798c2b6476830, 0xda12fe02287e9e77, 0x7aa3fba1c355b17a, 0x722d362f84614fba}}, .y = {.limbs = {0xe38da76dcd440621, 0x988d00bcf79af25d, 0x5b29c094db2a2314, 0x6d003afd41943e7a}}},
        {.x = {.limbs = {0xa8f2c94e19d9d829, 0xecb4b17f84f42d8c, 0x1e988d693df4a1fb, 0x659032865ff5154c}}, .y = {.limbs = {0x3f1d72d253a01dfc, 0x462e21f336a8971d, 0xfad3da15d691efa4, 0xf9ddc14e86be1ebf}}},
        {.x = {.limbs = {0xaf3c423a95d9f5b3, 0x054754efa150ac39, 0xcd29552fe3602573, 0x62dfdecef4053b45}}, .y = {.limbs = {0xf98a3fd831eb2b74, 0x9a93b0e6f35cfb40, 0xc8cd5aa667a15581, 0xbc2feded498fd9c6}}},
        {.x = {.limbs = {0x2773840fcf4e9e45, 0x9c052cebbfbb7e9d, 0xfd6b072c4fbb8d47, 0x6e37b93c5c478840}}, .y = {.limbs = {0xcc26479830e10370, 0x74eaa876aa416cf5, 0x9afd48bbc2a2cfb4, 0x9d3a95324e543c49}}},
        {.x = {.limbs = {0x766dbb24d134e745, 0xcccaa28c99bf2749, 0x06bb66b26dcf98df, 0x8d2fed50d884249a}}, .y = {.limbs = {0x744b1152eacbe5e3, 0x8dcc887980da38b8, 0x97584a65fa06cedd, 0x2c924f97cbac5996}}},
        {.x = {.limbs = {0x96516a8f65774275, 0x278d0d7420a88df0, 0xac44bd64c7bae07c, 0x3fe397c5b3300b23}}, .y = {.limbs = {0xbdacd9a05fb9fb73, 0x108c0a99d567fba9, 0xb2f75ab36207e155, 0x7f6bf255f1337ff0}}},
        {.x = {.limbs = {0x59dbf46f8c94759b, 0xa21277c33784f416, 0x45f7b44f6c596a58, 0xce92e666191abe3e}}, .y = {.limbs = {0xc534ad44175fbc30, 0x0f4ea6ce648309a0, 0x42ce739a7919798c, 0xd85e216c4a307f6e}}},
        {.x = {.limbs = {0x2ddf7bbcfe114e80, 0x7efe354db9f95fe7, 0x0e7e555bd9114950, 0xbb3d3d987058c8ae}}, .y = {.limbs = {0xec93e49c88fc8565, 0x2e754603b426bc0d, 0x90f3408491c470b4, 0xeb13f199399f4ec9}}},
        {.x = {.limbs = {0xf13ada95103c4537, 0x305e691e74e9a4a8, 0xdd647e711a95e73c, 0xb62dc6018cfd87b8}}, .y = {.limbs = {0xe13817b44ee14de6, 0x63bf4bc808341f32, 0x6949e21a6a75c257, 0x0778419bdaf5733d}}},
        {.x = {.limbs = {0xe9623bbef1bf90ec, 0x0d7c744ed34659f0, 0x10e6e63863716127, 0x0ecd31e14f87f62e}}, .y = {.limbs = {0x38a9743b4bc299e9, 0xe0fe953a8edaa929, 0xfe6043c9dd68844e, 0x53013eafa44ee737}}},
        {.x = {.limbs = {0x7754b4fa0e8aced0, 0x6d4167a2c59cca4c, 0xda1869c06ebadfb6, 0x488550015a88522c}}, .y = {.limbs = {0x30e93e864e669d82, 0x224b967c3020b8fa, 0x8d1e4e350b6cbcc5, 0x37a48b57841163a2}}},
        {.x = {.limbs = {0xe35bc6bb1b05b213, 0x0a37c28e771c6cb4, 0xbe89b397b454c8b5, 0x9e594fecc13b59df}}, .y = {.limbs = {0x21868874cc2cb5a7, 0x9c4d07d56a198dec, 0x358eb4e66a331b76, 0xc128b757cdd92acb}}},
        {.x = {.limbs = {0x948dcadf5990e048, 0xaa3874d46abef9d7, 0x01858f95de8041d2, 0xa6828c99e2262519}}, .y = {.limbs = {0xe491a42537f6e597, 0xd5d28a3224b1bc25, 0xdf9154efbd2ef1d2, 0xcbba2cae5347d57e}}},
        {.x = {.limbs = {0x87c01e27d84da2db, 0xd3330a7f05a58614, 0xa1ecdbabdcfccd39, 0xe5626baaf6812379}}, .y = {.limbs = {0x90e9991a7304206a, 0x64ef68644823be8a, 0x420e76859e59e54e, 0x0e5ec95ee2a1ecee}}},
        {.x = {.limbs = {0x7962414450c76c16, 0x89c7b48f8202ec37, 0xfb224cf5ac0bfa15, 0x70328a8a3d7c77ab}}, .y = {.limbs = {0x100b610ec4ffb476, 0x0d5c1fc133ef6f6b, 0x12507a051f04ac57, 0x60afa5b29db83437}}},
        {.x = {.limbs = {0x497c83c39c76e56d, 0x070fb906bced4409, 0x9de2d0e222575f22, 0xe4749682de46eeac}}, .y = {.limbs = {0x9807da341a297ee8, 0x4653a557449ff8b2, 0x7ae69493fda866f8, 0xa7ed795b923b9722}}},
        {.x = {.limbs = {0x3514087834964b54, 0xb15b160644d91548, 0x5a16977225b8847b, 0xb0dd085137ec47ca}}, .y = {.limbs = {0xef0afbb205620544, 0x8e1652c48e8127fc, 0x6039e77c15c2378b, 0x7e7d15a0de293311}}},
        {.x = {.limbs = {0xa8af384e794930e6, 0x3d81d3e1ef66cdab, 0x16d1cfda1b054da5, 0xf7086353a80c44fe}}, .y = {.limbs = {0xa24d6d07ede1cede, 0xcb32648c493af7de, 0xaf9915f0377906f1, 0xe3ab823d6581cc28}}},
        {.x = {.limbs = {0xd3cc30ad6b483e4b, 0xc79ce2c9dd8bc549, 0x93e947eb8df787b4, 0x42943d3f7b527eaf}}, .y = {.limbs = {0x8b378a22d827278d, 0x89c5e9be8f9508ae, 0x3c2ad46290358630, 0xafb34db04eede0a4}}},
        {.x = {.limbs = {0xeb49fd9f510469f4, 0xfe540e4b0664410f, 0x216cbbc90d97aed6, 0x2af2e606110cc919}}, .y = {.limbs = {0x6e638df7a9105bbc, 0x34db14f93706891d, 0x5d6406cbfcd76e17, 0x4c481324a6c8912b}}},
        {.x = {.limbs = {0x1624d84780732860, 0xce1c78fcbfefe08b, 0x2b29823db913f649, 0x3975ba0ff4847610}}, .y = {.limbs = {0x68651cf9b6da903e, 0x0914448c6cd9d4ca, 0x896878f5282be4c8, 0xcc06e2a404078575}}},
        {.x = {.limbs = {0xde1d35cbc6308cc5, 0xb435db84a21605a7, 0xd3a6172d6511c68b, 0xf6639d49c8704818}}, .y = {.limbs = {0xd03ce0b8ef7aa8aa, 0x2aaf43c6b4e4ebf1, 0x823ac662e052fa27, 0x75d5e1f0201f1ded}}},
        {.x = {.limbs = {0x733ce80da955a8a2, 0x6902c95633e62a98, 0x5192474b5af207da, 0x6df7b4fd5fc61cd4}}, .y = {.limbs = {0xf5435a2bd2badf7d, 0x485a4d8b8db9fcce, 0x3e1ef8e0201e4578, 0xc54673bc1dc5ea1d}}},
        {.x = {.limbs = {0x84df2e6e5e84cdff, 0x24120ca18648961a, 0xc134bcd7d6f35919, 0xbf6dcd5710e682f2}}, .y = {.limbs = {0x1d1d201c7c29525c, 0xc5339c7d978e3b74, 0x8935e6d57f30002a, 0x79b16d545167625e}}},
        {.x = {.limbs = {0x15d9441254945064, 0xcf1a1c33bbd3b49f, 0x8966c5092171e699, 0xef258dfab81c045c}}, .y = {.limbs = {0xd56eb30b69463e72, 0x34f5137b73b84177, 0x434800bacebfc685, 0xfc37bbe9efe4070d}}},
        {.x = {.limbs = {0x3f0e80e574456d8f, 0x8fa64e044b2eb72e, 0xa22eb53fe1efe3a4, 0x43933aca7f8cb0e3}}, .y = {.limbs = {0xcb66d7d7296cbc91, 0xe90b9c08485d01b3, 0x9501253aa65b53a4, 0xcb0289e2ea5f404f}}},
        {.x = {.limbs = {0xa1d0fcf2ec9de675, 0xb612136e5ce70d27, 0x1c21417c9d2b8aaa, 0xac138599d0717940}}, .y = {.limbs = {0xedd77f50bcb5a3ca, 0xb2e90737309667f2, 0x641462a54070f3d5, 0x19212d39c197a629}}},
        {.x = {.limbs = {0x4752f85486208311, 0x39bf1c39d65f194d, 0x191110fd2e9122ab, 0xd637ab63ef91e5b4}}, .y = {.limbs = {0xc80f1d852659b418, 0x6ec19e9ce26ae4bd, 0xb6f36b14fbf54ad1, 0x654f3ee5c9e6c1c2}}},
        {.x = {.limbs = {0xe22fbe15c0af8ccc, 0x5780c0735f84dbe9, 0xa790badee8245c06, 0xc7ca37331cb36980}}, .y = {.limbs = {0x0a855babad5cd60c, 0x88b430a69f53a1a7, 0xa38289154964799b, 0xe43d06d77d31da06}}},
        {.x = {.limbs = {0xed3bace23c5e1765, 0x2e174c835fb72bf5, 0x3ee306b3406a2689, 0x0221b4cef7500f88}}, .y = {.limbs = {0xe57a6f571288ccff, 0xdcda5e8a7a1f87bf, 0x97bd17be084895d0, 0xfce17ad5e335286e}}},
        {.x = {.limbs = {0x311091dd9860e8e2, 0x0ee13473c1155f5f, 0x69635e394704eaa7, 0x4009452246cfa9b3}}, .y = {.limbs = {0x66db656f87d1f04f, 0xffd1f04788c06830, 0x871ec5a64feee685, 0xbd80f0b1286d8374}}},
        {.x = {.limbs = {0x3049f7ffc71d744b, 0xd9bed6f42dc6a289, 0x74e3a1b9d30671f8, 0x00e5d46389103c7e}}, .y = {.limbs = {0xfae7bc16185fc1a6, 0x7f86709d01d2b66e, 0xdfefdefd1262bca4, 0xc7032f99470bef44}}},
        {.x = {.limbs = {0x34c1fd04d301be89, 0xb31c0442d3e6ac24, 0x883928b45a934078, 0x1867d4232ec2dbdf}}, .y = {.limbs = {0x09414685e97b1b59, 0x54bd46f730174136, 0xd57f1ceeb487443d, 0xc5321857ba73abee}}},
        {.x = {.limbs = {0x1880c9ad32fbb07e, 0x1fb52a688d9d6fe6, 0xdb0df90ecd4c9483, 0x203f636ee00926dc}}, .y = {.limbs = {0xa20c096cf36367bf, 0x0b7f1c9750e28afe, 0x99ac0b24e3a90c27, 0x0e6db815548473cc}}},
        {.x = {.limbs = {0xf219ea5d6b54701c, 0x1c14de5b557eb42a, 0x8d13f3abbcd08aff, 0xcc2a5e6b049b8d63}}, .y = {.limbs = {0x4cb95957e83d40b0, 0xf73af4544cccf6b1, 0xf4b08d3c07b27fb8, 0xd8c2962a400766d1}}},
        {.x = {.limbs = {0x1fc757d383e42507, 0x72310db34c1e79f3, 0x888043b17bcbe914, 0x90c7f04f8accb725}}, .y = {.limbs = {0xb4d0e7ef521c1c81, 0x9297ff08e74df0bd, 0x9a859739bea9b37e, 0x2f80fd5dc15e76bd}}},
        {.x = {.limbs = {0xd7b8740f74a8fbaa, 0xb1f683db8f45de26, 0x543a5490bca62708, 0x7236912469a0b448}}, .y = {.limbs = {0xfa77968128d9c92e, 0xe1010f337ad4717e, 0xff15db5ed3c049b3, 0x411e0315eaa4593b}}},
        {.x = {.limbs = {0x7e660beda020e9cc, 0x20391cef85374576, 0x853b0f22b8925d5d, 0x81c5845bb834c21e}}, .y = {.limbs = {0x2d114a5edb320cc9, 0x806527d1daf1bbb9, 0x6a8fedc6f9e8ead4, 0x21eaef2c7208e409}}},
        {.x = {.limbs = {0x32d31c222f8f6f0e, 0xf86f7c98d3a3335e, 0xad5bcd32abdd9428, 0x9fe4d3091aa824bf}}, .y = {.limbs = {0x5f3032f5892156e3, 0x9ccd3d7915b9e1da, 0x2e6dac9e6f26e961, 0x118d14b8462e1661}}},
        {.x = {.limbs = {0x3bb9aec1f1eb9ec7, 0xfa735fc4fcd0ab7c, 0x7b00f024a9728087, 0xf745ddaa42583d11}}, .y = {.limbs = {0x9ae0247b2342180c, 0x6af5b9dd4a6600d7, 0xcd14d9dd764d4726, 0x21ee1baef2bb04cd}}},
        {.x = {.limbs = {0x7461f371914ab326, 0x71045a155d9831ea, 0x8793d77cd59592c4, 0x340f86cbc18347b5}}, .y = {.limbs = {0x8ec0ba238b96bec0, 0xcbdddcae0aa44254, 0x2eee1ff50c986ea6, 0xb39847b3cc092ff6}}},
        {.x = {.limbs = {0xbc82dd73e5161dba, 0x0884a36f2080d682, 0xffc274bf62fca8f9, 0xeb0aadf82a8d733c}}, .y = {.limbs = {0xe5f28c3a044b1cac, 0x54a9b4bf719f02df, 0xae93a0bae7389730, 0x1e786104f47797f0}}},
        {.x = {.limbs = {0xee079adb1df18600, 0x74356a25aa38206a, 0x6d716b2c3e67453d, 0x287698bad7b2b2d6}}, .y = {.limbs = {0x8dc2412aafe3be5c, 0x4c5f37e0ecc5f9f6, 0xa446989af04c4e25, 0xebaac479ec1c8c1e}}},
        {.x = {.limbs = {0xb74f0c165b4a9435, 0x93cc339096d66ad5, 0x88d6b130b16695e5, 0xbd95ec557a93eab5}}, .y = {.limbs = {0x646fa5b5fcdad2d3, 0xbc306c9b6c15494a, 0x90ab454e65e5ec9e, 0x3b98e9611f5dc208}}},
        {.x = {.limbs = {0x16ec93e447ec83f0, 0x467b18302ee620f7, 0xe65de331874c9dc7, 0x2bfd8616ba9da6b5}}, .y = {.limbs = {0x5e4631150e62fb40, 0xd0e8c2a7ca5804a3, 0x9d58186a50e49713, 0x9626778e25b0674d}}},
        {.x = {.limbs = {0xfc6040fe245682cd, 0xf81eee193a3af355, 0xef6cc374ce143846, 0x9306fe7f8957f489}}, .y = {.limbs = {0x28312a55765d0435, 0xf656a354b9c92684, 0xed8bd517407373fd, 0x5d4e075e32808785}}},
        {.x = {.limbs = {0xeaa5f980c245f6f0, 0x38978290afa70b6b, 0xd8855897f98b6aa4, 0x85b96065d537bd99}}, .y = {.limbs = {0xf65f5d3e292c2e08, 0x19a528391c994624, 0xd784869d7e6ea67f, 0xb18041024edc07dc}}},
        {.x = {.limbs = {0xa7c0ea7395d87852, 0x53de84833ccffdb3, 0x1dc81f9c32bb84a5, 0x3ec1775d0fadae00}}, .y = {.limbs = {0xa26becc5ea1819d3, 0x3f876ff45961a83c, 0x19e16b89ce982871, 0xf58513f8fb152bce}}},
        {.x = {.limbs = {0x078c9407544ac132, 0x692ee1910a024399, 0x58ae04877151342e, 0xa96c4b6b35a49f51}}, .y = {.limbs = {0xf3e0319169eb9b85, 0xd5404795539a5e68, 0xfa1fbd583c064d24, 0x62b675f194a3ddb4}}},
        {.x = {.limbs = {0xdd5ba67cfb807824, 0xbd3ff25e9d1667fa, 0x89e7020e8e0becb7, 0x9caa00f574adc826}}, .y = {.limbs = {0xd6b837116fa89fa1, 0xd0d6e193aaaf5a56, 0x42425d84290545f2, 0x94a0753a915b644c}}},
        {.x = {.limbs = {0x494f4be219a1a770, 0x16dcd838431aea00, 0x01cdc8ae7a6fc688, 0x726578d9702857a5}}, .y = {.limbs = {0x42242a969283a5f3, 0x39ba7f075e36ba2a, 0xf925ce30d767ed6e, 0x55f4b031880d562c}}},
        {.x = {.limbs = {0x139ae46a1133f1f9, 0xd23f25efba0f6dd8, 0x7bf7ddaf568a5fb9, 0xe0a3bfda73176237}}, .y = {.limbs = {0x00995e555c8aabd2, 0x63fd238833a12188, 0xb8a5ffbeb480ba0e, 0x3e6ec481a8991472}}},
        {.x = {.limbs = {0xa598a8030da6d86c, 0x6bc7f2f5144ea549, 0xd28211ea58faa70e, 0xbf4c1e665c1fe9b5}}, .y = {.limbs = {0x204b5d6f84822c30, 0x7e4b4a7140737aec, 0x23fc63b65b35f86a, 0x10026dbd2d864e6b}}},
        {.x = {.limbs = {0xf90b89d53bdc724a, 0x685bb8c12419bbf5, 0xb8ffea50ec08422a, 0x9a7b09b1029471e3}}, .y = {.limbs = {0x672bd987c7e383ba, 0x1aaa132d75f7515f, 0x1a652cb086ee45d5, 0x7048c13feb4785f6}}},
        {.x = {.limbs = {0xc41916365abb2b5d, 0x09192f5f2dbeafec, 0x208f020f12570a18, 0x4dbadc3e58595997}}, .y = {.limbs = {0x04f14351d0087efa, 0x49d245b328984989, 0xd5caf9450f34bfc0, 0xed16e96b58fa9913}}},
        {.x = {.limbs = {0x6df7b5a7a126a611, 0x2e1e0ba01ad1a0f8, 0x9f055dd3c1c7e533, 0x6938ad32c494b319}}, .y = {.limbs = {0x9e2599b420982535, 0xb290cf45325af0b4, 0xa81efa6b414a583e, 0xeb09520a981fdf32}}},
        {.x = {.limbs = {0x841d6063a586fa47, 0x5a724604da03bc5b, 0x92a2e0d2e0a36acf, 0xe4c73a5514742881}}, .y = {.limbs = {0x073867f59c0659e8, 0x1904f9a1c7543698, 0xe62562d6744c169c, 0xe7a36de01a8d6154}}},
        {.x = {.limbs = {0x34ff3be4033f7a06, 0x696c3d09f7d1671c, 0xbcf55cd700535655, 0x647077456769a24e}}, .y = {.limbs = {0x5d9d11623a236c55, 0x3f6619d89832098c, 0x55df16c3e8f8b681, 0x8491067a73cc2f1a}}},
        {.x = {.limbs = {0x5e95bb399a6971d3, 0x76026947f89bde2f, 0x282b33810928be4d, 0xed112ac4d70e20d5}}, .y = {.limbs = {0x39f23f366809085b, 0xeebfc71181313775, 0xa99c9aed7d8ba38b, 0x161384c746012865}}},
        {.x = {.limbs = {0x9dda94404337db14, 0x74e67f1d7052f398, 0xa0e70ed205c5e94d, 0x6e731b06c6f51cd8}}, .y = {.limbs = {0x0065a58128f755af, 0xae6fae38ed6d2ec4, 0x306a0a11fdd22b0d, 0x7d5fa49229d31669}}},
        {.x = {.limbs = {0x36e4641a53948fd4, 0x76c39f8a99fd974e, 0x5ec07564b5315d8b, 0xf99471bca0ef2f66}}, .y = {.limbs = {0xd2424b1b1abe4eb8, 0x164227b085c9aa94, 0x56ea13493fd563e0, 0x6fd51cf5694c78fc}}},
        {.x = {.limbs = {0x8a93046d22897b40, 0x361bcd154301ff4b, 0x7ed3c170c45e44d4, 0x45d2ae2ae38947d7}}, .y = {.limbs = {0xb227f7d021263c6f, 0x29ca19b9110c315b, 0x43ddf472fbb16491, 0xe9002dccb1af50ce}}},
        {.x = {.limbs = {0x0336581ea7bfbbb2, 0x90c191a2f507a41c, 0xf5643842170e914f, 0xaeab27c2c579f726}}, .y = {.limbs = {0xead12168595fe1be, 0x99252129b6e56b33, 0x91f7ab1410cd1e0e, 0xf3dcdcabd2fda224}}},
        {.x = {.limbs = {0xd5f66020bdd383a8, 0x75e8b46dc5a91925, 0xf17d3f1f5eeafb4e, 0x2b1f39bec59b9618}}, .y = {.limbs = {0x8f8c3eec190df3d1, 0x11263a75d9328a1c, 0x879b9ab8e9b75d4a, 0x17c5de9e6f3aa216}}},
        {.x = {.limbs = {0x8ab89816dadfd6b6, 0xa1f2634fcf00ec84, 0x03781025ed6890c4, 0x849742706bd43ede}}, .y = {.limbs = {0x6fdcef09f2f6d0a0, 0x44e654aef624136f, 0x503d459c3e898458, 0x58a47a9129cdd24e}}},
        {.x = {.limbs = {0xf25f6e271e231dfd, 0x5f5f8d2aaf30fc6d, 0xafe835feca1575e9, 0x3f667f69d0d97018}}, .y = {.limbs = {0xbab2192b75324599, 0xd2946af2a8737bb6, 0x8be2ff17f252cebd, 0x369ee69a35b4af25}}},
        {.x = {.limbs = {0x1e33f1a746c9c577, 0x8133344d9299fcaa, 0x20b0938e8acff254, 0x4bb40284b8c5fb94}}, .y = {.limbs = {0x060660257dd11b3a, 0xa9c8ed618d24edff, 0x2306d320f1d03010, 0xe33a7d2057f3b3b6}}},
        {.x = {.limbs = {0x0f1dd626b9722019, 0x9541a803535b09dc, 0x6f0328bc6eda337b, 0x5ea937913ccf1095}}, .y = {.limbs = {0xf46bfb389fdb7ce4, 0x4286ae3f103a2074, 0xe17549340a46831a, 0xfeb77705fc25f516}}},
        {.x = {.limbs = {0x85b7c1dcb3cec1b7, 0xee7f30ded79dd20a, 0x0ed1f4cc18cbcfcf, 0xa410361fd8f08f31}}, .y = {.limbs = {0x3d98a9cdd026dd43, 0xf39048f25a8847f4, 0xfcafad1895d7a633, 0xc6fed3c35e999511}}},
        {.x = {.limbs = {0x9358bf4e626ce79a, 0x888c0a54ce408b48, 0xfa4acb89cd7d9487, 0xb92d2f1129289fa9}}, .y = {.limbs = {0x5af11032704e83d0, 0x57337b85ccacbb62, 0xb34905a2087e6a25, 0x5530a39d2e8d7639}}},
        {.x = {.limbs = {0x29df9fbd8d9e4650, 0x9275f4b125d6d45d, 0x7fbe9a3b878a7af8, 0x72a2800661ac5f51}}, .y = {.limbs = {0x0b4c4fe99c775a60, 0x6e2d8862179139ff, 0xda61dc861c019e55, 0xcd2876eb2a27d84b}}},
        {.x = {.limbs = {0xef68a2c7ad33241d, 0x6adc31b4e7830036, 0xb5e571af914fe014, 0xc9f81b66ff472adb}}, .y = {.limbs = {0x202632e371066766, 0xe8842c4bfd67c46c, 0x2abe221a176d0e2e, 0x786ef55ebe29887e}}},
        {.x = {.limbs = {0xa0b1cae06b0a847a, 0x3fea6e671aaf8adf, 0xdfe58ca2f768105c, 0x8082b2e449fce252}}, .y = {.limbs = {0xae434102edde0958, 0xec4b19d917a6a28e, 0x6b72da1834aff0e6, 0x50f049503a296cf2}}},
        {.x = {.limbs = {0x8e3d1248c7657211, 0xd20291ce1798f490, 0x743f1bc852858e32, 0xd7efe2315fbc7671}}, .y = {.limbs = {0x099a48e10ecfcb81, 0xf64480e19393e90e, 0xb9352baaa63e144a, 0x7ef1dc6418717dec}}},
        {.x = {.limbs = {0x04e8ceafb9b3e9a1, 0x36dc7ff67e840295, 0xb499dfb3b2133e4b, 0xa113f2e4c0e121e5}}, .y = {.limbs = {0xcf2174118c8b6d7a, 0x4b48f6d534ce5c79, 0x422c086a63460502, 0xb827ce62a326683c}}},
        {.x = {.limbs = {0x7b732af34077f331, 0x08a0e679d9eea6a8, 0x1cf5e707c8f3050d, 0x5dfb298429952152}}, .y = {.limbs = {0x17c4d13c535be360, 0xb92fd08559ee2a71, 0x3e0012f6af5c01df, 0x8f163904bad1c7cf}}},
        {.x = {.limbs = {0xd24a44e047e19b6f, 0x5afb81c7ca2f6908, 0x0a5076689a010919, 0xf42725c2b789a33b}}, .y = {.limbs = {0x6fb8d5591b466f8f, 0xc63db50f1c0f1c69, 0x013f996887b8244d, 0x2cdec417afea8fa3}}},
        {.x = {.limbs = {0xecc99b0cf89ef141, 0x2718197ef17ed087, 0x6f02c24fbb10ae46, 0xdf051b79da14b6c3}}, .y = {.limbs = {0x04abcdd05201e8bd, 0x598a5284fc790673, 0xe7c5f702206dc0e8, 0x6d5c41a70c1e9fdb}}},
        {.x = {.limbs = {0xea01606a7a6c9cdd, 0x249fdfcfacb99584, 0x001edd28abbab77b, 0x5104e98e8e3b35d4}}, .y = {.limbs = {0x322af4908c7312b0, 0xcfbfe369f7a7b3cd, 0xb7d4494bc2823700, 0xcfd652188a3ea98d}}},
        {.x = {.limbs = {0x1f6014569d1203ae, 0x0c128ac00a410976, 0x09b16386bde7f857, 0xb908ea95e5eebbef}}, .y = {.limbs = {0x82b83f8d79ec4b86, 0x5a75a2a70908f483, 0xafe9f96231d1d1c2, 0x91475348ac0dce51}}},
        {.x = {.limbs = {0xaf8addbf2b661c8a, 0x6c6328655eb96651, 0x252007d8c5ea31be, 0x4ad196de8ce2131f}}, .y = {.limbs = {0x6749e67c029b85f5, 0x2a034eafd096836b, 0x2520818680e26ac8, 0xf3dfbcdb71749700}}},
        {.x = {.limbs = {0xe19d8d416b28eeef, 0xb603b7d515377322, 0x2f127b76ff24d7b8, 0x419eb6997dee8d17}}, .y = {.limbs = {0xa54b0056fbeb471b, 0x0fc534d42aecc459, 0x0e2268c7d1679757, 0x266e2d163fc83d99}}},
        {.x = {.limbs = {0x00e3ae1974566ca0, 0x6cc516d47e0fb165, 0xa674a3dabcfca15e, 0x722f0e3450f45889}}, .y = {.limbs = {0x2aeabe7e45315101, 0x16217f07bf4d0730, 0x0de97e4874f81f53, 0x3420a72eeb0bd6a4}}},
        {.x = {.limbs = {0x9ea5c218b98cc990, 0xbf7257c3b588e75b, 0x4a03a9c0107e1d63, 0x8e7b0a261f997190}}, .y = {.limbs = {0xa049b1f4eefc6732, 0xe74e6b0c79b53775, 0x9fabf3e9a060bd70, 0xbd249eeb28a2fea2}}},
        {.x = {.limbs = {0x591ee355313d9972, 0x1cf6993ffed1e3e3, 0x01993ff3ed258802, 0x075ea8ced397e246}}, .y = {.limbs = {0xb0ea558a113c30be, 0xa60fc4775460c790, 0x1ff0b053d25ca2bd, 0xeee98f1a4be5d196}}},
        {.x = {.limbs = {0xa8be67d40815919c, 0x5f13c7cc84c166d5, 0x5e603eb6750077ac, 0xd7a17c18f15a3699}}, .y = {.limbs = {0x6db068bbf5499243, 0x189b5d017f8fdb76, 0xbab1d00db0dbc03a, 0x65a2b31f88196c47}}},
        {.x = {.limbs = {0x11396d55fda54c49, 0xf19aa97318d8da61, 0xfa8584e47b084945, 0x077cf03255b52984}}, .y = {.limbs = {0x998c74a8cd45ac01, 0x289d5833a7beb474, 0x4ff536b01b257be4, 0xc5767bea93ea57a4}}},
        {.x = {.limbs = {0x915050c28c39ebfd, 0x36ecbe198e90fe71, 0xa53573822a6e94b3, 0x0f734afb0a29f390}}, .y = {.limbs = {0x51559be325b4d6d6, 0xde8682090b6ec098, 0x87a558dadae0c580, 0xc121316a8ded4293}}},
        {.x = {.limbs = {0x3c5d2a1ba39c5a17, 0x90000738c9e0c40b, 0x8dcdfd5468754b64, 0x05540157e017aa7a}}, .y = {.limbs = {0xb2284279995a34e2, 0xf9d4de7396fc18b8, 0x0f9b8b9fdd270f66, 0x61f79ca4c81bd257}}},
        {.x = {.limbs = {0x308913a27a52d922, 0x2bc776838f73f576, 0xa4d047122a9b184b, 0x05ec32ad51b03f6c}}, .y = {.limbs = {0xf4a5b09543febe5f, 0x91e3531f66c0375d, 0xa8333fea82bd1f12, 0x60ab5efce8fe4c67}}},
        {.x = {.limbs = {0xcc8704b8a60a0def, 0xa3a99a7299f2e9c3, 0xfbc395afb04ac078, 0x425ef8a1793cc030}}, .y = {.limbs = {0xbdd46039feed1788, 0x1d1e0862db347f8c, 0xf395b74fc4bcdc4e, 0x940b74e3ac1f1b13}}},
        {.x = {.limbs = {0xfbaf4eb5bdf8fe93, 0x97a3b8bc51bfa271, 0x83ff4ac34a966eb8, 0x22109700780a7943}}, .y = {.limbs = {0x36e7ff517ad79fab, 0x6571de2ed92bcc04, 0x8209f6506fe4c0ff, 0x52c0bb205d654a9d}}},
        {.x = {.limbs = {0xc533e4f7ea8555aa, 0xcd9777ac5cad29b9, 0x7dd4defccc53ee7e, 0xa204119b2889b197}}, .y = {.limbs = {0x6f0a256bc5efdf42, 0x9a2fb6242f1a43a2, 0xd9b925bb4a4b3a26, 0xbb8e0f45eb596096}}},
        {.x = {.limbs = {0xf62885ce55ff7be2, 0x91dd96717159e106, 0xb77beeb53920db82, 0xa218a7bda715e7ba}}, .y = {.limbs = {0x74eb8317416fe8fd, 0x656df2f95983cff2, 0x52bfe6a7b0deab60, 0x7eb8538d1da95407}}},
        {.x = {.limbs = {0x0c14f8f2ccb27d6f, 0x109f6d08d03cc96a, 0x69ba8c34eec07bbc, 0xf566d48e33da6593}}, .y = {.limbs = {0xc359d6923bb398f7, 0xfd4473e16fe1c284, 0x75b740dd098075e6, 0xc0e8649113dc3a38}}},
        {.x = {.limbs = {0xa5822bd06c673e21, 0xb41f30c4efd7c491, 0x09f00c12cdc12c51, 0x56835fe50c9d3205}}, .y = {.limbs = {0xa3bcd62645ceba65, 0x487708ebeb652d9f, 0x19b58fa4588cb4f5, 0xb35f4eda136d08a8}}},
        {.x = {.limbs = {0xa6cbc3046bc6a450, 0xbac24789fa17115a, 0x4c9739ed75f8f21c, 0xe441f72e0b90e6ef}}, .y = {.limbs = {0x021ae7f4680e889b, 0xb130619e2c0f95a3, 0x60ceb573c7060313, 0x9862afd617fa9b9f}}},
        {.x = {.limbs = {0x328ba6c70c404497, 0xa663505914704a7b, 0x695331569d729745, 0xbaa1f1cdcbf2d359}}, .y = {.limbs = {0xc8ecc2845917b7ff, 0xa518bdc4c4e812e4, 0x287d8f897b2b1b47, 0x4a6efe1a786fce55}}},
        {.x = {.limbs = {0x347d6d9a02c48927, 0xebfb86c1359b1caf, 0x130a3c0267d11ce6, 0x344b39f99d43cc38}}, .y = {.limbs = {0x60ea7f61a353524d, 0x1c987f6ecec92f08, 0x6d565ab687870cb1, 0x2689ff1e31c74448}}},
        {.x = {.limbs = {0xf9502d540ca7d5ab, 0x09ea89e83889fa4b, 0xcd0b27f7eec5752f, 0x4fa07b1b19160f3b}}, .y = {.limbs = {0xa10ce6db4859d825, 0xc4ba2fbd12803a7b, 0xb6822f65e0a7a93b, 0x6b71df5b05c81ae8}}},
        {.x = {.limbs = {0xda6545d2181db8d9, 0x83f7dcb375ef5866, 0xd47c67b1bf31c8cf, 0x855ef7437b72656a}}, .y = {.limbs = {0x49b96715ab6878a7, 0x9e78f07ce5680c5d, 0x6673051b4935bd89, 0x7fea824b77dc208a}}},
        {.x = {.limbs = {0xc4f942ea2b52a8ce, 0xf06e95d0665a4073, 0xd9c41961f668fdb6, 0x8464ab4070ab2b7a}}, .y = {.limbs = {0xc6bd3cdf50b11f93, 0x99a77f7feabe8213, 0xecbde264616c3f61, 0x3592fc86703dad66}}},
        {.x = {.limbs = {0xc40747cc9d012cb1, 0xa13b8148309c6de7, 0xec25d6945d657146, 0xb9d5994b8feb1111}}, .y = {.limbs = {0x5ca560753be2a12f, 0xc6de6caf2cb48956, 0x5db936156b9514e1, 0xbb5e83037e0fa2d4}}},
        {.x = {.limbs = {0x69317694d15b16c5, 0x48fc20ec98691ed6, 0x838230a85b762e92, 0xfa4f1bc1da40f082}}, .y = {.limbs = {0xe39a66553ac9f9d6, 0x3f5624422bbc0abc, 0xd61a7ec68024807a, 0x4def01604ed38e14}}},
        {.x = {.limbs = {0x4e42c8ec82c99798, 0xccf3a610be870e78, 0x338c7f713348bd34, 0xc8203ef4037f3502}}, .y = {.limbs = {0x7571d74ee5e0fb92, 0xa7a8b33a07783341, 0xa5492144cc54bcc4, 0x0a94473693606437}}},
        {.x = {.limbs = {0x78a891aa2234a498, 0x896a193ed088a2b6, 0x8fcae82788f506a0, 0xf3287432beb31db2}}, .y = {.limbs = {0x6912a35beb5035cb, 0xfcf5f25527302df6, 0x54379bcdd800b82d, 0x3069d623b9fa4343}}},
        {.x = {.limbs = {0x3775ab7089bc6af8, 0x23aba2e1af70b236, 0xd251cadb0c867432, 0x87522a1b3b0dedea}}, .y = {.limbs = {0xbe52d107bcfa09d8, 0xbcb9736a828cfa7f, 0xac8db17bf7a76a2c, 0x42ad961409018cf7}}},
        {.x = {.limbs = {0x192e787021b1e83e, 0xad4572c55b488607, 0xdcb079365966c543, 0x7632c5c33e4cb721}}, .y = {.limbs = {0x6c8e5d14a501c926, 0xd84c22cdd600ef63, 0x81c36d5c8710bb68, 0xbfd1e93bf71e23b9}}},
        {.x = {.limbs = {0xcee31cbf7e34ec37, 0x9d94fb814d3d775a, 0xd954595d1314ba88, 0x46959e3e82f74e26}}, .y = {.limbs = {0x8fd64a14c06b589c, 0x26b947ae2bcf6bfa, 0x0149ef0be14ed4d8, 0x0f448a01c43b1c6d}}},
        {.x = {.limbs = {0x8267f5f35e78f30d, 0xcf58f7bc65a2514d, 0x0c8c0ac8d1f6b993, 0x74818ee88f5e524f}}, .y = {.limbs = {0xb5cdcb48ee2cdcd6, 0x8ecc5e35e976f77e, 0xc67205e31e72c170, 0x21ab2902da0ff381}}},
        {.x = {.limbs = {0xb4f9eaea09b69176, 0x19f6ea6a4eb5464e, 0xfddb58fd45b1ebef, 0xcdc1a01d08b47986}}, .y = {.limbs = {0x39e5c9925b5a54b0, 0x7433a4f18c61726f, 0x8bb131c012ca542e, 0xb24a8ac07200682a}}},
        {.x = {.limbs = {0xa076cacf92cc467c, 0x94ed72da5b996139, 0x5dacf1a224b15755, 0x9169e4ea2b19a602}}, .y = {.limbs = {0xa213cbd11f2c882d, 0x043e203fe3b8c422, 0x10770ad296a01ad0, 0x449d42ee37e65fa4}}},
        {.x = {.limbs = {0xd4263dfc3d2df923, 0xa0179a48966d30ce, 0x84e2515afc3dccc1, 0xb77907792ebcc60e}}, .y = {.limbs = {0x62dfaf07a0f78feb, 0x30e30d6295853ce1, 0x89e127760ad6cf7f, 0xae164e122a208d54}}},
        {.x = {.limbs = {0x4265bbaf8d442ac5, 0x162aaae1836a64aa, 0xb9e912769ef3393f, 0x395681815f5be39c}}, .y = {.limbs = {0x3140b915410c1212, 0x87a3b97e37fd2230, 0x9d4552d208e1e7e2, 0xb3fa2102457cf151}}},
        {.x = {.limbs = {0x48457524820fa65a, 0x4f8d35eb6930857c, 0x0032acc0a4a2de42, 0x2233eeda897612c4}}, .y = {.limbs = {0x25a748ab367979d9, 0x8733c38a1fa1c2e7, 0xdc6cc07db2d60a9a, 0xe7a76aaa49bd0f77}}},
        {.x = {.limbs = {0x3e805fa563758c7b, 0x2187ee0a7a4e2503, 0x495f3686c9351822, 0xb054d3844f1724c1}}, .y = {.limbs = {0xe74d9c8f8463ea37, 0xec1daf204a51288a, 0xcc12918983bf74f0, 0x0b4eeba071b0594b}}},
        {.x = {.limbs = {0xdfeeef1881101f2c, 0xb11644f3a2afdfc2, 0x045e19919152923f, 0x367a1767c11cceda}}, .y = {.limbs = {0xecfb7056cf1de042, 0xf9420bab396793c0, 0xc390bde74b4bbdff, 0x16a83ae09a9a7517}}},
        {.x = {.limbs = {0x296eef5bdd483af1, 0xec401a7fa0f5db8b, 0x75a7adb1b1596240, 0x75f3d8ef294845f3}}, .y = {.limbs = {0x94de12d051e62940, 0xf9a51421b1549bce, 0x2b1de5b2d1d3bd8c, 0xcf85d393d3f2f8bf}}},
        {.x = {.limbs = {0x6d7ef6b17543f837, 0x3c573f44e1f38983, 0x5d89bcbc6062ced3, 0x6c82df83b8fae859}}, .y = {.limbs = {0xcd450ec335438986, 0xdfefa10c57fea9bc, 0xc521a0959b2d80bb, 0xf74b190dca712d10}}},
        {.x = {.limbs = {0x32c001f5785688f6, 0x2416f0ae4ed51ec8, 0x5d8db3a2dc56b8b1, 0xe63065b098bbae2e}}, .y = {.limbs = {0xe662b869a22227b3, 0x657cc56cf6e46ad1, 0xfac71452a632431f, 0xfcfcc8fc7c306316}}},
        {.x = {.limbs = {0xe75605d59102a5a2, 0x684500d3b991f2e3, 0xf3c88b9322554703, 0x5af25af66e04541f}}, .y = {.limbs = {0xf5c54754a8f71ee5, 0x40b9b48728473e31, 0x4f729ac5308b0693, 0x8360990e2bfad125}}},
        {.x = {.limbs = {0xd7a0da58d01dc635, 0x812ddf64d99c9aea, 0xe783c797d7cd204e, 0xc7b750f733ce1752}}, .y = {.limbs = {0x912770e068008032, 0xf6f2928340e28465, 0x0be040a8c062b742, 0xbbc027380762cef4}}},
        {.x = {.limbs = {0xeb98660f4c4dfaa0, 0x6a2be453d5020bc9, 0x9a0c2e60abe38845, 0x7dd43fefb1ed620c}}, .y = {.limbs = {0x6cb9a8876d9cb852, 0x0609af3add26cd20, 0xa0a7cd8a9411131c, 0xe85f44100099223e}}},
        {.x = {.limbs = {0x838ed2eb98f46685, 0x3b4ab50f6b1030ce, 0x1d8742af3a39049a, 0xd0f9cf8031bdc863}}, .y = {.limbs = {0x836ed454d94c9199, 0x495ba885d9b8b819, 0xfc9adb6c57d54c9c, 0xaee700ea6c6ae32f}}},
        {.x = {.limbs = {0x13e87b027d8514d3, 0x5939f2e6892b1992, 0x2154596941888336, 0xdc3563e3b8dba942}}, .y = {.limbs = {0xfef5a3c68059a6de, 0xc5d624114bf1e91a, 0xac2b9da568d6abeb, 0x2570d55646b8adf1}}},
        {.x = {.limbs = {0x21c76dbf7a8d075a, 0x88b4262217960359, 0x64f08ea3aa575d8f, 0x5f2d7ca5d86e196e}}, .y = {.limbs = {0xd67286b1d5716401, 0xdcae9bd97378bd4a, 0xa25f0cbd2a296656, 0xbc8f0186ccf45c5a}}},
        {.x = {.limbs = {0xee163026e9fd6fe0, 0x17c38f06a5be6fc1, 0x25424b371ce2708e, 0x7bf4491691e5764a}}, .y = {.limbs = {0x1acb250f255dd61c, 0x43d94ccc670d0f58, 0xf49ae3fa15b96623, 0xe5430da0ad6c62b2}}},
        {.x = {.limbs = {0x93e651f2d3ac2659, 0xe38b59ba5857b83c, 0xfe3f31125f3bc5bc, 0x6a0c81bd90877ed5}}, .y = {.limbs = {0x907308b0980c45ce, 0xdc34a72350ea5d40, 0xbf27585f4b1ac1ed, 0x8cf83c556d73af84}}},
        {.x = {.limbs = {0xb268f5ef9ad51e4d, 0x78de3a750c2dc89b, 0x1e626d4350586799, 0x9932e5db33af3d80}}, .y = {.limbs = {0x5f310d4b3c99b9eb, 0xb19f77d41c1dee01, 0x8cf0d34fd4191614, 0x003e945a1216e423}}},
        {.x = {.limbs = {0xcd5a3be41717d656, 0x83fe7a9de8ae5b4b, 0x8feced69f26a8b55, 0xeeefbcc2e74b75fb}}, .y = {.limbs = {0xfd6381eaf29657fd, 0xb1373fbba578001e, 0xfa92c34b1f38c89f, 0x9c0b605ba95832a5}}},
        {.x = {.limbs = {0xff07f3118a9df035, 0xe9fad85eb6c7bfe4, 0x2b02f01ca99ceea3, 0xbf7ffdba93c4750d}}, .y = {.limbs = {0x438136d603e858a3, 0xa5c440c38eccbadd, 0xc1d2942114e2eddd, 0x4740d098ced1f0d8}}},
        {.x = {.limbs = {0x6c0d1f1784e47ff0, 0x4108c1d9049df6b3, 0x658aa6490ef4ef1a, 0xc1e4dbfd90ac0427}}, .y = {.limbs = {0xef9a8bd1525f4864, 0x413bd16e1749ee18, 0x4519a730a32e2265, 0x1f5262f7887b72af}}},
        {.x = {.limbs = {0x8d8b9855c7c052a3, 0x4146fd20ffb658be, 0xa4b9f69e0d825ebe, 0xc16e8c3ce2b526a1}}, .y = {.limbs = {0xcdb559eedc2d79f9, 0x26baf44fb84ea4d4, 0x4bcf50fee51d7ceb, 0x30e2e7f463036758}}},
        {.x = {.limbs = {0xda9b9e9ab699c11c, 0xef8b8cdbd452f7c5, 0xca6dd9da7a9efa19, 0xacc0a89758554b6c}}, .y = {.limbs = {0xec8598c45d39f0e0, 0x75bb7a8e714e885e, 0x01faaf5675484185, 0x25c560257be95bdb}}},
        {.x = {.limbs = {0x52db0b5384dfbf05, 0xbfa9d472d7ae26df, 0xe4b851ceca91b1eb, 0xa54263180da32b63}}, .y = {.limbs = {0x0c3b997d050ee5d4, 0x23ebaf66a6db9f57, 0xb3180c902875679d, 0xe924b69d84a7b375}}},
        {.x = {.limbs = {0x52520de6009c7e49, 0xf080ea4c21a2ade2, 0xd2f58220c30a7cb0, 0x56fc4c098ad30369}}, .y = {.limbs = {0x9d0a6b077d71cc3b, 0xf4c888520bd33955, 0x4f3003efe1b2802c, 0x350d54cfe47bf50b}}},
        {.x = {.limbs = {0xe62f9490d3d51da6, 0x395efd24e80919cc, 0x7d0f29c3f3fa48c6, 0xfff543becbd43352}}, .y = {.limbs = {0x6d89ad7ba4876b0b, 0x22c2ca280c682862, 0xf342c8591f1daf51, 0x70e07bfd9ccafa7d}}},
        {.x = {.limbs = {0x7d86781855db1b17, 0xd7ce3765816076eb, 0xa7163cb9fba082bb, 0x65348f778db0e595}}, .y = {.limbs = {0xe2b99adfec86f877, 0x2e562e2bed4f8838, 0x2937844e0e25d532, 0x99951e3abc733de8}}},
        {.x = {.limbs = {0x7f30ea2476b399b4, 0x957509c88f77d019, 0x1afa2ff5cb7b14fd, 0x6d8e7d65aaab1193}}, .y = {.limbs = {0xca5ef7d4b231c94c, 0x3b15389a5f6311e9, 0xdaff7bb67b103e98, 0x80ef4bff637acaec}}},
        {.x = {.limbs = {0x59ae134c1a41cfee, 0x81c5c2cd51ac727b, 0x4e7759552d729e07, 0xb25031df15661815}}, .y = {.limbs = {0xe0c2821689a92635, 0xbd7df32296a9fc38, 0x847a414a8455218d, 0x09cda7f01e8bfc2b}}},
        {.x = {.limbs = {0x5098ff1e1d9f14fb, 0x46a210fada6c903f, 0xef0fb7b4a1dd1d9a, 0xc60a0361800b7a00}}, .y = {.limbs = {0x09731141d81fc8f8, 0x084d37c6e7542006, 0xb3ee1b40d60dfe53, 0x62a5b132fd17ddc0}}},
        {.x = {.limbs = {0xf4a0caad9ad20992, 0x5131b1389effbbd2, 0x8615402eb31f2c08, 0x2cf6531fd68befd5}}, .y = {.limbs = {0x3cbf5c99286222f4, 0x64fe48656b101b58, 0x7fd5a3ae8ba8b4b1, 0x2dbd7a76b1b9c8b9}}},
        {.x = {.limbs = {0x32b78c7de9ee512a, 0x72895be6b9cbefa6, 0xe2f3c4ccce445c96, 0xb9f2c81e2778ad58}}, .y = {.limbs = {0xee1849f513df71e3, 0x2efc3896ee28260c, 0x73bb80547ae2275b, 0xa497237794c8753c}}},
        {.x = {.limbs = {0xb40226a37a1a586d, 0x0b360ad75ee73fab, 0xac67947361320882, 0xa8f9e0cfb9746ecc}}, .y = {.limbs = {0xf7ce91842e49e9d4, 0x1f8d4a3e21ace469, 0x5226c0d3cf24c4af, 0x48e525620a13060c}}},
        {.x = {.limbs = {0xe2cb74fddc8e9fbc, 0xd076eef2a7c72b0c, 0xe37d50f08269dfc0, 0x74b581550547a4f7}}, .y = {.limbs = {0xd3aa2ed71c9dd224, 0x7a62df062736eb0b, 0xaddea9e36122d2be, 0x8641abcb005cc4a4}}},
        {.x = {.limbs = {0x54bebc996f6c2b7c, 0x52ac321ea930afa6, 0x66c2f828ca99facc, 0x577e0ffa43b4f3bc}}, .y = {.limbs = {0x15276d9145b9bcaf, 0x2bebede498e028d8, 0x041eae9f117b3e34, 0x2a3619ad0de244e9}}},
        {.x = {.limbs = {0x8438447566d4d7be, 0xdadc299496ab3574, 0x26009a35f235cb14, 0x1be0d99cd10ae3a8}}, .y = {.limbs = {0xc4e1020916980a4d, 0xa5d01ac5e6ad3307, 0x34ef0d7906631c4f, 0x2390426b2edd791f}}},
        {.x = {.limbs = {0xcea8d97ae24caebb, 0x2bba4eff99c743dc, 0xcac732be31e1b614, 0x34d667b8fad96201}}, .y = {.limbs = {0x03e6b5491eb5219d, 0x1da077543ce0b7f1, 0xb25e0a780fdea14e, 0xc90774f6baa7e834}}},
        {.x = {.limbs = {0x4162d488b8940203, 0x9b584c6fc6c30887, 0x0587d9c46f660b87, 0x8ab65c82c711d67e}}, .y = {.limbs = {0x67163e903236289f, 0x776f22c25fb8a3af, 0xc1732f2b84b4e95d, 0xbda47ae5a0852649}}},
        {.x = {.limbs = {0x4b24649ac96f264f, 0xd12ef9ca0a34b068, 0xf84b6f6249ae3d7d, 0xfc9caa19ff32151e}}, .y = {.limbs = {0xc98998be4c613a7a, 0x2ab27141690ab859, 0x81c434d346df5e0c, 0x62f3b896e8369787}}},
        {.x = {.limbs = {0x3fad3fa84caf0f34, 0xf0f89bfd2dcf54fc, 0x175d767aec3e5068, 0x4f3ba4a4bf5f683d}}, .y = {.limbs = {0x0cd1bc7cb6cc407b, 0xb2f0ca647c718a73, 0x0cf71872e7d0d2a5, 0x3fa20efcdfe61826}}},
        {.x = {.limbs = {0xbdc6c1b0f061c563, 0x243061575dc28b48, 0xa562847bec1b88b6, 0xf600bbde5b2c74a4}}, .y = {.limbs = {0xca7a42daf8694c62, 0xb40a81e852827b8e, 0x64d28821559fcedc, 0x716409cc8bab85ae}}},
        {.x = {.limbs = {0x674f2600a3007a00, 0x568c1a7ce05d0816, 0xc1fb84bf1370798f, 0x1c69532faeb1a86b}}, .y = {.limbs = {0x299d21f9413f33b3, 0xedf43b257004580b, 0x70db57da0b182259, 0xe09eecc69e0d38a5}}},
        {.x = {.limbs = {0x08bc89c2f919ed15, 0x8885c35600844d49, 0x890905c79b357322, 0x609c45706ce6b514}}, .y = {.limbs = {0xd313f3cdd7cdcc16, 0xde776fec3b5892c1, 0x172d3056112776f0, 0x6f63f4cea8c95157}}},
        {.x = {.limbs = {0xd32f4da54ade74ab, 0xb81b815ad1fb3b26, 0x3d82d6c692714bcf, 0xf87d29bd5ee9f08f}}, .y = {.limbs = {0xf9429e738b8e53b9, 0x68e99016c0597077, 0x82e14f4535359d58, 0x2fc416910b3eea87}}},
        {.x = {.limbs = {0x714651a9cb4af14c, 0x78ac98661e39723d, 0x234d56537053d014, 0x0f08670f188ce2bc}}, .y = {.limbs = {0x28b6d7837004120f, 0xaa11b1ab6f7ec0f3, 0xf1f902c744e425bd, 0x2dd668c1fd617cc6}}},
        {.x = {.limbs = {0x30e4e67043538555, 0x6e593657135845d3, 0x6fbb6931f72b08cb, 0x1ed954f1e3ce3ff6}}, .y = {.limbs = {0x462f9bce61989863, 0x8499350113bbc9b1, 0x0a878d35da70740d, 0xc695a559eb88db7b}}},
        {.x = {.limbs = {0x7e62469c0893fc16, 0x61fa0449250cd2a5, 0x7558b9e8d46130c1, 0x25149eed98fe1249}}, .y = {.limbs = {0x60f803c2b44d43a0, 0x0dfcaef6a82b9c7c, 0xf80beb233dbd9df7, 0xdf02760aea9e0a2c}}},
        {.x = {.limbs = {0xbe2062003c51cc30, 0x04682904330e4dee, 0x7f3dcd10b01e580b, 0xf1971b04d4cad297}}, .y = {.limbs = {0x62188bc49d61e542, 0x8573d48a74e1c655, 0xb1c61090905682a0, 0xd5558ed72dccb9bc}}},
        {.x = {.limbs = {0x0639863c5cf03696, 0x867960f4f378473f, 0xafddfed53ea14522, 0x6b51046bf16e839b}}, .y = {.limbs = {0xc130794479f2bb77, 0xc2a5bc741deeb71a, 0xd00e3228bf1eb99d, 0x1fca864423d1c1be}}},
        {.x = {.limbs = {0x93144423ace3451e, 0xd29e0fb9ac2af211, 0xcb6e84a601df5993, 0xc419859fff5df04a}}, .y = {.limbs = {0x7c10dfb164c3425f, 0x5c71a3f9d7992038, 0xf1065224f72bb9d1, 0xd902a6d13037b47c}}},
        {.x = {.limbs = {0x7d54261d569c7330, 0xa5b943abdd4a0d7f, 0x2fb1f35ea3adc41f, 0x422049a122517961}}, .y = {.limbs = {0xb52974a37a1c5e94, 0x77559bdc7f1017d1, 0xefdd509a19c63e56, 0x63add999d2f95bb3}}},
        {.x = {.limbs = {0xb015f8044f5fcbdc, 0xf21ca26d6c34fb81, 0x97829205c7b7d2a7, 0xcb66418c157b112c}}, .y = {.limbs = {0xab8c1e086d04e813, 0x744a655b2df8d5f8, 0x3b3cdc6faa3088c1, 0xd3aea1454e3a1d5f}}},
        {.x = {.limbs = {0xb35511d67e63fa65, 0x52db740b48aba6d2, 0x30c21799e65a6647, 0xa5cbfc789ef0184b}}, .y = {.limbs = {0xc8eed15dfa36bca2, 0x8d859b3982343dea, 0x91930cd46322a119, 0x7dc74cec622a5995}}},
        {.x = {.limbs = {0xd5e9e1da649d97d8, 0x9e4868117a465a3a, 0x4f8a18de57a140d3, 0x6b3f2af341a21b52}}, .y = {.limbs = {0x4cb04437f391ed73, 0x111a13cc1d4dd0db, 0x1693465c2240480d, 0x8955e8592f27447a}}},
        {.x = {.limbs = {0xe485be3daccabfab, 0x0e0ca7b596da918d, 0x7f0107d535274c94, 0x9683baab330bff95}}, .y = {.limbs = {0xc4071fd9f1b90283, 0x30c621e8aab586a1, 0x7c0834f9544168fc, 0xdf71e1abdcfd8fb6}}},
        {.x = {.limbs = {0xd3ae41047dd7ca06, 0x5dbf8ed77b992439, 0x983005cd72e16d6f, 0x996a5316d36966bb}}, .y = {.limbs = {0xbd1aeb21ad22ebb2, 0x2a10f0303417c6d9, 0x64f8cdd7df0aca61, 0x4b10dc14d125ac46}}},
        {.x = {.limbs = {0x0659214ac1a17900, 0x23f53c4cf55a0a63, 0xb9e20c1151efa971, 0x215b395a558aa151}}, .y = {.limbs = {0xb126363aa4243d27, 0x59320a356230569a, 0x4eea355d9dabd94e, 0xd7f4590701e5364d}}},
        {.x = {.limbs = {0x463e2763d885f958, 0xfc66cdd22800f0a4, 0x87197d0a82e377b4, 0x9f80af87c897b065}}, .y = {.limbs = {0xbfefacdb0e5d0fd7, 0xdf3a311a94de062b, 0x26b80c61fbc97508, 0xb79992671ef7ca7f}}},
        {.x = {.limbs = {0xddc5310f00582ac8, 0x48494b9dc41ab086, 0x76545f84205e6a2a, 0x008fef8516060dfc}}, .y = {.limbs = {0xba0d2f3af20d9692, 0x0191ab6dcc8f0e90, 0x41dbafc6abd04730, 0xfb5f8ab6e7820ca8}}},
        {.x = {.limbs = {0x7985fdfd127c0567, 0xc6f53ec1bb63ec31, 0x58e597c40bfe747c, 0x83cddfc910641917}}, .y = {.limbs = {0x603c12daf3d9862e, 0xf2b25fe1de289aed, 0x24ed291e0ec67087, 0x03a5bd567f32ed03}}},
        {.x = {.limbs = {0x6a843ba43c244f89, 0xa8f86c708c25f0e1, 0x4d8e2df756ef139d, 0xf3ed516ed7c504ef}}, .y = {.limbs = {0x63dad3922e66cdfb, 0x58643c3feb2cfac6, 0xf8cba1b16a19b8f2, 0x3112844dcab0af01}}},
        {.x = {.limbs = {0x74a1ad6b5f76e39d, 0xb2dd249410eac7f9, 0x9e74c59cb83d2d0e, 0xd5ff1543da7703e9}}, .y = {.limbs = {0xcc6157ef18c9c63c, 0xd6193d83631bbea0, 0x093e0968942e8c33, 0xd5737fd790e0db08}}},
        {.x = {.limbs = {0x2e34552aa716aef7, 0x5edf6a1f8a10dff8, 0x636478cbbff1713a, 0x5fc0da4813704a08}}, .y = {.limbs = {0xfc822d5ea0c68b76, 0x8c9cbafee51f97a0, 0x64782b5a3885ab58, 0x4e44de8e79598a01}}},
        {.x = {.limbs = {0x30682a50703375f6, 0x02d416664ba19b7f, 0xc9bab42c72747463, 0xa71d0896b22f6da3}}, .y = {.limbs = {0x553e04f6b018b4fa, 0x6c8f39e7f311d317, 0x6290d0e0f19ca73f, 0x17714d9977a22ff8}}},
        {.x = {.limbs = {0x00136933174bc388, 0xa74ebd6746e13afe, 0x0eef5d66580c8e23, 0xd33464c342dc0080}}, .y = {.limbs = {0x27015dc47dbfe781, 0x689f232541c04105, 0x60ac69c82044e8e5, 0x906e54680127ff92}}},
        {.x = {.limbs = {0x9e2158f0d7c0d5f2, 0x6c3791efefa79597, 0x654e7a2b2464f52b, 0x1ee6c1347769ef57}}, .y = {.limbs = {0x0712fcdd1b9053f0, 0x9003a3481fa7762e, 0x9ffd7c8ef35a3850, 0x9e2fbf2629008373}}},
        {.x = {.limbs = {0x22213b78f3dcfbdf, 0xeb76cc1731c1ba31, 0x8b2b0c32f081e206, 0xf50618fa7eaf5aa3}}, .y = {.limbs = {0xdd81b694ec3a60ba, 0xd2a203d8eedc863f, 0xe476add5cf739174, 0x0d86e5c8718a3051}}},
        {.x = {.limbs = {0x176e26989a43c9cf, 0xeba4029c202538c2, 0x8172e566e3c4fce7, 0x322857f3be327d66}}, .y = {.limbs = {0xed8cc9d04b29eb87, 0x7d270b4878dc43c1, 0x9aefd31f4eee09ee, 0x7b47834c1fa4b1c3}}},
        {.x = {.limbs = {0x8758a9fd232f0fe9, 0xa7afc8456a40d57b, 0xc46e2a586d37641c, 0x2d6c77bcac938f93}}, .y = {.limbs = {0x5cc678a31a3b536c, 0x0c0ab2c94a8e89e6, 0xe22e369309ac3c4e, 0x7863ac2a068f7866}}},
        {.x = {.limbs = {0x75d46efea3771e6e, 0x68abb89a13ad747e, 0xcf1892393dfc4f1b, 0x7004788c50374da8}}, .y = {.limbs = {0x9852390a99507679, 0xfd0b86fd2b39a868, 0xd7efc22151346e1a, 0x3ca4726586a6bed8}}},
        {.x = {.limbs = {0x69b47c7249439d23, 0xa5f3c28db17e60da, 0x861a483939a113e2, 0xd903e0547bb26bfb}}, .y = {.limbs = {0x1a9cf6cd7c7ad92a, 0xfd37e43c0d6230c6, 0x43590d98e54e5678, 0x0b08824df1978ea2}}},
        {.x = {.limbs = {0x809a20c67d64900f, 0xfb698c4c825f6d5f, 0x2310fb0451c86934, 0x5b7319f645605721}}, .y = {.limbs = {0x9e994980d9917e22, 0xb76b061927fa0414, 0x3d096ccc54963e6a, 0x5ebfa5f3f8e286c1}}},
        {.x = {.limbs = {0x5654834268843e72, 0xc300e97d5188fca2, 0xed04459e09ca4351, 0x475a62c4bc8ade53}}, .y = {.limbs = {0x1b33a3362bc07380, 0x19cf1c838c69253c, 0xc6ddcc39676e2ea1, 0x69394d2089481e75}}},
        {.x = {.limbs = {0x1b38903a43f7f114, 0xed4500b4eac7083f, 0xdefece1cf29c6352, 0x8d563446f972c180}}, .y = {.limbs = {0x4036edc931a60ae8, 0x89353f77fd53de4a, 0x2708b26b6f5da72a, 0xd3394119daf408f9}}},

    };

    JacobianPoint jacobian_result_point;
    JacobianPoint tmp_point;

    unsigned long long limb;

    unsigned long long is_not_first_non_zero_window = 0;

    unsigned long long mask_use_g_times_window = 0;        // we do not had a non-zero window yet - this window can be zero or not
    unsigned long long mask_sum_g_times_window = 0;        // window is not zero and this is not the first non-zero window
    unsigned long long mask_do_not_sum_g_times_window = 0; // window is zero and is not the first non-zero window

    for (unsigned char limb_index = 0; limb_index < 4; ++limb_index)
    {
        limb = scalar->limbs[limb_index];
        for (unsigned char i = 0; i < 8; ++i)
        {
            jacobian_double_point(&jacobian_result_point, &tmp_point);
            jacobian_double_point(&tmp_point, &jacobian_result_point);
            jacobian_double_point(&jacobian_result_point, &tmp_point);
            jacobian_double_point(&tmp_point, &jacobian_result_point);
            jacobian_double_point(&jacobian_result_point, &tmp_point);
            jacobian_double_point(&tmp_point, &jacobian_result_point);
            jacobian_double_point(&jacobian_result_point, &tmp_point);
            jacobian_double_point(&tmp_point, &jacobian_result_point);

            unsigned long long window = limb >> 56;
            unsigned long long window_is_not_zero = !!window; // bool

            mask_use_g_times_window = -(!is_not_first_non_zero_window);                                                     // mask
            mask_sum_g_times_window = -(window_is_not_zero & is_not_first_non_zero_window);                                 // mask
            mask_do_not_sum_g_times_window = -(((unsigned long long)(!window_is_not_zero)) & is_not_first_non_zero_window); // mask

            is_not_first_non_zero_window = is_not_first_non_zero_window | window_is_not_zero;

            jacobian_point_affine_point_addition(&jacobian_result_point, &g_times[window], &tmp_point);

            jacobian_result_point.x.limbs[0] = (g_times[window].x.limbs[0] & mask_use_g_times_window) | (tmp_point.x.limbs[0] & mask_sum_g_times_window) | (jacobian_result_point.x.limbs[0] & mask_do_not_sum_g_times_window);
            jacobian_result_point.y.limbs[0] = (g_times[window].y.limbs[0] & mask_use_g_times_window) | (tmp_point.y.limbs[0] & mask_sum_g_times_window) | (jacobian_result_point.y.limbs[0] & mask_do_not_sum_g_times_window);
            jacobian_result_point.z.limbs[0] = (tmp_point.z.limbs[0] & mask_sum_g_times_window) | (jacobian_result_point.z.limbs[0] & mask_do_not_sum_g_times_window);

            jacobian_result_point.x.limbs[1] = (g_times[window].x.limbs[1] & mask_use_g_times_window) | (tmp_point.x.limbs[1] & mask_sum_g_times_window) | (jacobian_result_point.x.limbs[1] & mask_do_not_sum_g_times_window);
            jacobian_result_point.y.limbs[1] = (g_times[window].y.limbs[1] & mask_use_g_times_window) | (tmp_point.y.limbs[1] & mask_sum_g_times_window) | (jacobian_result_point.y.limbs[1] & mask_do_not_sum_g_times_window);
            jacobian_result_point.z.limbs[1] = (tmp_point.z.limbs[1] & mask_sum_g_times_window) | (jacobian_result_point.z.limbs[1] & mask_do_not_sum_g_times_window);

            jacobian_result_point.x.limbs[2] = (g_times[window].x.limbs[2] & mask_use_g_times_window) | (tmp_point.x.limbs[2] & mask_sum_g_times_window) | (jacobian_result_point.x.limbs[2] & mask_do_not_sum_g_times_window);
            jacobian_result_point.y.limbs[2] = (g_times[window].y.limbs[2] & mask_use_g_times_window) | (tmp_point.y.limbs[2] & mask_sum_g_times_window) | (jacobian_result_point.y.limbs[2] & mask_do_not_sum_g_times_window);
            jacobian_result_point.z.limbs[2] = (tmp_point.z.limbs[2] & mask_sum_g_times_window) | (jacobian_result_point.z.limbs[2] & mask_do_not_sum_g_times_window);

            jacobian_result_point.x.limbs[3] = (g_times[window].x.limbs[3] & mask_use_g_times_window) | (tmp_point.x.limbs[3] & mask_sum_g_times_window) | (jacobian_result_point.x.limbs[3] & mask_do_not_sum_g_times_window);
            jacobian_result_point.y.limbs[3] = (g_times[window].y.limbs[3] & mask_use_g_times_window) | (tmp_point.y.limbs[3] & mask_sum_g_times_window) | (jacobian_result_point.y.limbs[3] & mask_do_not_sum_g_times_window);
            jacobian_result_point.z.limbs[3] = (1ULL & mask_use_g_times_window) | (tmp_point.z.limbs[3] & mask_sum_g_times_window) | (jacobian_result_point.z.limbs[3] & mask_do_not_sum_g_times_window);

            limb <<= 8;
        }
    }

    jacobian_to_affine(&jacobian_result_point, result_point);
}
inline void g_times_scalar_antigo(const Uint256 *scalar, Point *result_point)
{

    static const Point g_times[256] = {
        {.x = {.limbs = {0, 0, 0, 0}}, .y = {.limbs = {0, 0, 0, 0}}}, // will never be used
        {.x = {.limbs = {0x9981e643e9089f48, 0x979f48c033fd129c, 0x231e295329bc66db, 0xd7362e5a487e2097}}, .y = {.limbs = {0xcf3f851fd4a582d6, 0x70b6b59aac19c136, 0x8dfc5d5d1f1dc64d, 0xb15ea6d2d3dbabe2}}},
        {.x = {.limbs = {0xf918623ccba0ee23, 0xce0b62e1e0140404, 0x71354afc88b285a0, 0x4e0640c981048d2c}}, .y = {.limbs = {0x3c7f7712157b9313, 0x4b3a0f64bda2cc65, 0x84fd25167dc75ce1, 0x7d12d622ffaccfbf}}},
        {.x = {.limbs = {0x9497730fcdf4c0ad, 0x5940d07385985972, 0x066ceafb22eb7bc4, 0x2379d4bbd5fea781}}, .y = {.limbs = {0x3ec28dcd9215ec76, 0xcc6048bd84885650, 0xac4964cdc5a1f91f, 0xaf18b0b0613f55a9}}},
        {.x = {.limbs = {0x1957e6951ca769b7, 0xde9fbe79f9b379e0, 0x37571e4d3b9b132f, 0x3daa13e8af6a0bfd}}, .y = {.limbs = {0x4c9a2dbb209e02b9, 0xc3e5bac23d6a1839, 0x746dd1bf9400d136, 0x1372e87e5bf5eae9}}},
        {.x = {.limbs = {0x8ed284d3aae7f96f, 0x20ce358572dd41dd, 0x58d7334ddc284cda, 0x212347fcbea19bc6}}, .y = {.limbs = {0x1fd437ae583630c0, 0x011d0b107f8dbfd2, 0x59aaa8d8aad35cc5, 0x9e5e784800dfd9e7}}},
        {.x = {.limbs = {0x5c8088490f91fa73, 0x5d84dcf301b5b366, 0x534e4de75355fe43, 0xd409e08fe568f5bc}}, .y = {.limbs = {0x0175b14f2060a9c3, 0xb9a0411797c737a7, 0x7ba780ad82ae93be, 0x5dee0bf9c6a6b4ca}}},
        {.x = {.limbs = {0x5f402433d73866e0, 0x4da362224e1d6bd5, 0xca934f8716c087c4, 0x07ece566caa4cb22}}, .y = {.limbs = {0xc8043a670ba1a73b, 0xf2fd13d87291ab04, 0x879d7639f1097263, 0x4777d1124a77d752}}},
        {.x = {.limbs = {0xc3088630cfa83a8c, 0x376af358ab408c8b, 0x7a060c0bfa606728, 0xf23162063e0b48a5}}, .y = {.limbs = {0x85b43f9979490860, 0x75193c47f1ea48b2, 0x7b292c94ece7dd34, 0xceb03c71452c2cfb}}},
        {.x = {.limbs = {0x87d71c6bf4d02a72, 0x8cec72c7f64b253d, 0x6edd9e7f1ed7f74c, 0x46cc6d26eafd5a74}}, .y = {.limbs = {0x0156339094cef97c, 0xf0176bede6793574, 0xaec108c659794d80, 0xb2a0d4ae268d25a4}}},
        {.x = {.limbs = {0xe8cf0172cea73b48, 0x70b8c02edea2464f, 0x8c5126a2be40abcd, 0x55ca2987f7784248}}, .y = {.limbs = {0x0d3a934a99eddb2e, 0x60333362dddeea91, 0x466360215d4daacc, 0x6136fd68e49bc235}}},
        {.x = {.limbs = {0x9d888be8bce5a953, 0xd28558b5bb49a3c1, 0x349ebdf993493bb8, 0x04f0c78f94a7a0aa}}, .y = {.limbs = {0x0e92c06d7705fac8, 0x7cb76bd27b41572a, 0x755db980f899acaa, 0x434322e37beacf4c}}},
        {.x = {.limbs = {0x5a1ba91650a32c5e, 0x5cc8065afd6bde73, 0x5b0037a9b5f4abae, 0xb915e5812095e799}}, .y = {.limbs = {0x61aa286044355c42, 0xc11a025902c73651, 0x2a531f7e16ce529f, 0x0c75cf5be50a193d}}},
        {.x = {.limbs = {0x7065f32baff18f7b, 0x5b370e50a02a9988, 0xd35438e646aec93f, 0xd59a06c4f5989088}}, .y = {.limbs = {0x595e4c3399b24984, 0xdb37e3a6c013f5af, 0x0f73d052948a3b41, 0x14817536a5d44558}}},
        {.x = {.limbs = {0x8482dda73ed47ea2, 0x15e738ff050c28c8, 0xf82a3045078e2e49, 0x1e9cce5fd119938b}}, .y = {.limbs = {0x875e4a09819b112e, 0xccaac1084b900c72, 0x9df244f15309b645, 0xdfeaa54cac7e1635}}},
        {.x = {.limbs = {0x329cf6f36a78a2b1, 0x8fe0d087f9180a0e, 0xa9b174243ff3bffd, 0xd51e8da318620cd4}}, .y = {.limbs = {0xf384d03b4965bc3e, 0x1442e0ed9e703fc8, 0xd97359fb5ca29845, 0x364e94e68cf9083a}}},
        {.x = {.limbs = {0xb7f2007d526d9948, 0x952ed69488f3f45a, 0x78d77162cf43dec5, 0x41a38518efe247fb}}, .y = {.limbs = {0xa46b9ec0f2e973c0, 0xe6e1d02ce631ad75, 0x35538b908855c928, 0xb252bfb837528726}}},
        {.x = {.limbs = {0xe272a6a1f9ff59aa, 0x69d7a2a822b91922, 0x9b182865f3b25560, 0xd90bb8e11df00c43}}, .y = {.limbs = {0xb9d1058538a1624e, 0x4e936ddcc6b65cc3, 0x99dc58b3753707e5, 0x85352ea76f2a14c9}}},
        {.x = {.limbs = {0xef9c5b0a0439349c, 0x6f3dba88a5dece13, 0xcc8fbdf745693c50, 0xe09aceaee77f7a20}}, .y = {.limbs = {0x6eb891fd8dc35bb0, 0xcf4f5d2dd27c9659, 0x001c91d670041a77, 0xb156dbc6f45ad225}}},
        {.x = {.limbs = {0xdeb7636c4dd633a5, 0xd8d133ada3023a4a, 0x5f8bf03a727df8f4, 0xd78ee564d62a7a38}}, .y = {.limbs = {0x444ec627d07c28ea, 0x7ceef09600dda4f2, 0x91a29c6198b88bdc, 0xdf15c738e0d36289}}},
        {.x = {.limbs = {0xd5430d14a3d9b51c, 0x7abf8ae62f69b0da, 0x4cef653382a9bbc8, 0x8ad822b3c875e295}}, .y = {.limbs = {0x297d11a216f62808, 0x71830200844a2b0d, 0x1b122f3bc3bdcc0d, 0x039a9a21705ad9be}}},
        {.x = {.limbs = {0x38d21ce5a746f598, 0xe0a1107e6cb12ea3, 0x6ddb2dc674eacc1d, 0x7287d563f76ce60a}}, .y = {.limbs = {0x9a760529af0be6c8, 0xd69265aeb8025098, 0x439ddfdc4c4c0573, 0xead831a434cae6f2}}},
        {.x = {.limbs = {0xfbccf5c7dd29779e, 0x784a6da32e70a605, 0x932d5bdc5c0116b7, 0xe8c5c366b73e4a91}}, .y = {.limbs = {0x56041ef73ac4df6b, 0xc678ca75999000c2, 0xe71b520ec89dc5e4, 0x442f6ff4f513ddd4}}},
        {.x = {.limbs = {0x34b9089136060918, 0xb2bb768f928ba6aa, 0xb7018dcca66fa9a0, 0x710c24917d7868e2}}, .y = {.limbs = {0x1ada75eb956c455f, 0xfabc5a81934fc6c9, 0x04e41eb805d5c130, 0x1bb37e7d5a765cfa}}},
        {.x = {.limbs = {0x553c031285536ab6, 0xead011df611eb42a, 0x4485de9faac15990, 0xcfeb83687120202e}}, .y = {.limbs = {0xa062a1371f5941f0, 0x6e1fe9b9e4385e3b, 0x85f1090f0f508400, 0x9fbdd9e37240f1c3}}},
        {.x = {.limbs = {0x4f13fd3db6487c5a, 0x826674bbf7fb2c09, 0xcc7c3aff84257eee, 0x43a8673a528eab6d}}, .y = {.limbs = {0xdaaf22e5b81ac1bd, 0x315a735beaaa2d4c, 0xd788f352bb5bb569, 0x1af88d5c37027b74}}},
        {.x = {.limbs = {0x0298e7d5be8af66b, 0x2d84e9b56e887dd7, 0x5f849b69b88af5f1, 0xf746484ebc3e0277}}, .y = {.limbs = {0xad00c6153dcd4458, 0x352e52d491c7f763, 0x14168780696ecb70, 0x70dd4db0ae7ba72a}}},
        {.x = {.limbs = {0x6753e5a765719926, 0x4a77f053b730aeba, 0xf732d13664c270e8, 0x4065de4bdf096d18}}, .y = {.limbs = {0x5dace33180153d3b, 0xfbfcc60cd3304a23, 0x5987c3f8ac9dcfb6, 0xca06688145d3e40b}}},
        {.x = {.limbs = {0x9e8ad8b2969dc755, 0xe89f5c5698b44128, 0xbe2a99c7cb3d03c0, 0xdb27e02ae3848537}}, .y = {.limbs = {0xeaac1ce111d0b6f6, 0x63337ca3846a6d59, 0x9dc042c8e5216308, 0x2614d543b58e0b4e}}},
        {.x = {.limbs = {0x30822abdd5a92b77, 0x8c4c7f2072cecebe, 0x66de27b31124aa09, 0x78393cc1bc66aebf}}, .y = {.limbs = {0x210ec24f6535ce88, 0x0cdb3ab31afa8c27, 0xcb952fa172bd2977, 0xa8c8e083f7cbcb31}}},
        {.x = {.limbs = {0x3f731feadfd4a7fd, 0xa97f6fc865f6f533, 0x4d1a8ed0a549b38e, 0xd78ad319ea37d02f}}, .y = {.limbs = {0x5df3fde88f2788ce, 0x8738726189de9864, 0xa9b0401bb96d7efb, 0xaa7392cf9361e8f7}}},
        {.x = {.limbs = {0xf12c7e23f74ec811, 0x730d41a484012e67, 0x016f76f7b2686256, 0x3eeec4b21af2746f}}, .y = {.limbs = {0x27964839bfa868aa, 0x5e0eda4ce149b499, 0x10ac2b51ca2335dd, 0xe5694678a89357dc}}},
        {.x = {.limbs = {0x98d1c0e47be6cf23, 0x93e19cc4fe000a29, 0xacc8229d708ed243, 0x7c2cd2b54d6a3d31}}, .y = {.limbs = {0xbd734a1a4359aeab, 0x408bc0f94e530eb0, 0x7674374a341f8cab, 0x7d04a29f553f37ee}}},
        {.x = {.limbs = {0x37b49275a8134188, 0x87e088c16ce63ae1, 0x83266b6f7948d55c, 0xc789b0d904462042}}, .y = {.limbs = {0x79fb211f777f178a, 0x03dbb3810cef8e10, 0xf698b243c499bb93, 0x55856bfe2b18110c}}},
        {.x = {.limbs = {0x7d65278595381a34, 0xd1cef5e0456abb8a, 0x9e2f30062b419efc, 0x6b48bb4da29092e5}}, .y = {.limbs = {0x076a9f903ebf669c, 0x20a18ea5fdd2ba43, 0xf82b92e1d207756a, 0x1bccc7a02d314242}}},
        {.x = {.limbs = {0x581042a66f6f64c8, 0xa06b283acf667258, 0xaf885b4de6947cc4, 0x8cc030b523eacd0a}}, .y = {.limbs = {0xc7ec3e2d5b411868, 0xbd0a4fadaeabe161, 0x4dc9de4c5eab6ebe, 0x3a31e3d79265f180}}},
        {.x = {.limbs = {0xedbf560dbf9d57ee, 0x2a0d38b31dc488e1, 0x93b20803e8476efb, 0xc86d641cff5a336a}}, .y = {.limbs = {0xaa91e9f2e299cf45, 0x7ea8c8fb86711b08, 0xc4165b263df70ec9, 0xc86df9d6cde9b9e5}}},
        {.x = {.limbs = {0x621a29ddb92d0518, 0x198bd86cd6081a8f, 0x85755869ed7e7a80, 0x574d374d611e5431}}, .y = {.limbs = {0xce9b6976d67d796d, 0x8985db78e11526fa, 0xc1be6826da9fddb4, 0xf231989edd9866d8}}},
        {.x = {.limbs = {0x4e6f96f1d34822fe, 0xb70cef08313f9762, 0x8a3896532a26cf7d, 0x95f68adc03938a1e}}, .y = {.limbs = {0x4b98ffd2b4d2e26b, 0xd5ec29d7453b87eb, 0x84e15cfbb6519ce3, 0xd07a5a7adb7a66cd}}},
        {.x = {.limbs = {0x77de6bba5c326551, 0x5e723a3d524477f9, 0x8c686ce20af3d47a, 0x0abb6b74931ab84a}}, .y = {.limbs = {0xcf35e3ebf5a3d880, 0xf5482095c7aafa37, 0xaeb7c6cde49d0496, 0xfc5b9ec5929b6f64}}},
        {.x = {.limbs = {0x676e0b270aba4d02, 0x352e2ae03997035a, 0x35eeee59d3122d05, 0x3d45dcaa871c4c13}}, .y = {.limbs = {0x6b9a869c73c22f20, 0x8878498762dc79c0, 0x2596ee915d3c4a70, 0x0454f89807ef599c}}},
        {.x = {.limbs = {0x2e2bc80567214653, 0x146dbbc189c1812d, 0x86f719df0dc5b44e, 0x0ae480b9f53d193c}}, .y = {.limbs = {0xc00969e9383240ea, 0x18e6c1b219f23c9b, 0x4ba332cb7d576c11, 0xfcbb7632be39d872}}},
        {.x = {.limbs = {0x3545677c45d8dacc, 0x57ac09873dcb4ab0, 0x00772e020f563b5f, 0x790fbc076029ebec}}, .y = {.limbs = {0xa0a1827aa5dcc38d, 0x73d62ab3f03f9be9, 0x0382e69bc8fab0f0, 0x884d9dd440835633}}},
        {.x = {.limbs = {0x37c6a02e65a48803, 0xa93c93521597f957, 0x3cc9b7d466f160b7, 0x5f294ba4f83f38d0}}, .y = {.limbs = {0x962e84ea6bea9faa, 0xf3df54f6d45360dc, 0xd90d585c5b5ad049, 0xbe0809ba4c8dde97}}},
        {.x = {.limbs = {0x30c28068a42fbbb1, 0xfa95bac4db217aa4, 0xa010efbd0e172033, 0x8a909a28159de74f}}, .y = {.limbs = {0xf1cef3f85ab4d5f5, 0x150d4416b86e0212, 0xf40842924036382f, 0x027c08257b539a7e}}},
        {.x = {.limbs = {0x2ca518ad5320b144, 0x83c92f9d42552668, 0xc20713edd5081d8f, 0xba3684679efa4969}}, .y = {.limbs = {0x578756f29e6ffca5, 0x854ec8102c544b3d, 0x3b30690ebe289c86, 0x5afa94ed90e0c05c}}},
        {.x = {.limbs = {0x5e61bc2abe67cd30, 0x5804d5b1fc9bb6cb, 0x1c764035af1fbc90, 0xb4ca6680313e1d59}}, .y = {.limbs = {0x6f21c3037ba1c5ef, 0xede7fc359a4e1cd9, 0xe1c22eb5f53b530b, 0xf9026fda1d38a9e9}}},
        {.x = {.limbs = {0x3233ef661cbf1211, 0x49cb06514d1fb544, 0x86ae5c96ae5cb8cf, 0x16a6d6de472adca1}}, .y = {.limbs = {0x3f188c560425b0d4, 0xe4bc5f988ae74268, 0x4fc6f53994c7e45a, 0x3b47757649e7e82b}}},
        {.x = {.limbs = {0x67f338a8324f752b, 0xe27a77c09f7a0825, 0x4f830ca098772e8e, 0x44e9157911b93177}}, .y = {.limbs = {0x63d34ea8c4e44cf4, 0xd265a3edae4252b8, 0xae2754732a87a305, 0x8300d9846306576a}}},
        {.x = {.limbs = {0xa1482a269bb97205, 0x6c08f60d4e310ef5, 0x7ee70afdde7df977, 0xdef9f1d0d939d060}}, .y = {.limbs = {0x6db77a1a2e1da593, 0x33364421d8a95257, 0xba1f50ed769367ab, 0xcdd9f40c80d483ec}}},
        {.x = {.limbs = {0x05bc20a20a75002c, 0x6e31352af4790502, 0x612b80e31b33f0e2, 0xe9db21e6cd02463d}}, .y = {.limbs = {0x08250debf7b665a8, 0x9d8fc4b9a931198c, 0x394804e4b1c27fbb, 0x61cc98a7d54f33f2}}},
        {.x = {.limbs = {0x6e3c4f4ff2d3984e, 0xead948d305d0d2e9, 0xc36b65f01919ed5f, 0x4fba1057d6d499e6}}, .y = {.limbs = {0x73f7d2d32d273a4b, 0xd266f00b330ddbf7, 0xc22c7b5f8a4f8771, 0x02b72b3fd133daef}}},
        {.x = {.limbs = {0xd29e7a57eb92c8a4, 0x7b736eecd1f39df5, 0x5f7b175f3de6c39e, 0xcec5ceb1b093df83}}, .y = {.limbs = {0x7be08a79a71f1a6c, 0x22b0f71d2235ecda, 0x5cb6f450dc917e8c, 0x08dd3ab70f095b53}}},
        {.x = {.limbs = {0xaf6ceb12f4eb9bb7, 0xde7b34cf7d19e5a2, 0xe5fd9e62f139f8c5, 0x29aba0f99b4ad7c2}}, .y = {.limbs = {0xf2edddf9b0e45726, 0x83dadee963e0338d, 0x55c8772e06865b9b, 0x980e43acd79eb786}}},
        {.x = {.limbs = {0x2cfae1da466c83ee, 0x1854ad9d98f7811a, 0xd5d9503aa4e53e47, 0x7992658675426676}}, .y = {.limbs = {0x127d3151e74f4390, 0x8b59f3cad8bc61ea, 0x96bcd92016f569dc, 0x57c16d76735c23f6}}},
        {.x = {.limbs = {0xc7b06ee96985fced, 0x8f1c07dc6c8c357e, 0x2483921e02fad43d, 0x51666ffc2e9be15e}}, .y = {.limbs = {0xba398de3910b0743, 0xf26df73f7be3572a, 0x5528e849bbb2db21, 0xcc6e1536c6b46c3e}}},
        {.x = {.limbs = {0xc4b9dbb6c4da0682, 0x51d2ce623432dfb6, 0x5cfc29d94aea4e1f, 0x642165e03cf5332e}}, .y = {.limbs = {0x42c46858e70f10dd, 0x09760b4072355b70, 0x581c935e67767df4, 0x5adfc3d1924e75f4}}},
        {.x = {.limbs = {0x3130c25b4b0d1b30, 0xe4be3476e040dc88, 0xb47a5180e1e6e3e4, 0x117a547cc70c9cbc}}, .y = {.limbs = {0xc6ea984d4b832e71, 0x877f57ddfe4216bc, 0x1bdbea3650d3fb9a, 0x040d4f07cf2a1cef}}},
        {.x = {.limbs = {0xd482660d7315e904, 0xdbdfe9e8a26dafeb, 0x81d1060dfa42526d, 0xe8e86043e7823826}}, .y = {.limbs = {0x0dd2a3b9c268724d, 0xe0a30f650572c2c9, 0x208c7a535610f7ca, 0xb112d5d00a362621}}},
        {.x = {.limbs = {0xfb31e37630f720ed, 0x9500ddd625037408, 0xa154e2bd7761b2b0, 0x8fefc57423cf448a}}, .y = {.limbs = {0xcad37dfaab3dfe73, 0x4c8df8bb5b38bc15, 0x9c4d7e1a6b6d0049, 0xd1b658150b2b3069}}},
        {.x = {.limbs = {0x07a26cfff6e7f95b, 0x18142397d4c10217, 0x3d3746ff88f6b978, 0x670d2378b032e04a}}, .y = {.limbs = {0x35662548590695f3, 0x4062a53c9704ea21, 0xb24694f8d1fde62e, 0x19c1220ee896d71a}}},
        {.x = {.limbs = {0xa2930635cd40829a, 0x83f9faf08450e538, 0x7f125440b549b012, 0x3b75bb5de9b540e1}}, .y = {.limbs = {0x866090e27c885dc0, 0x367fdcf5e6112ff9, 0x398e268e4889b425, 0x73f89d79daed83c2}}},
        {.x = {.limbs = {0x5197cb546b88a272, 0x6f71c19992cdc3d3, 0x3a6bb93da079fb0e, 0x69ed18cb27a93f61}}, .y = {.limbs = {0x2820390433a587eb, 0x8356e9657428e8d2, 0xea75123bfb176ffe, 0x630ca631de128b56}}},
        {.x = {.limbs = {0x3539752caa4356f4, 0xffda5b3f839c0518, 0xdea61ae4b9f7c408, 0xa4d44416639300be}}, .y = {.limbs = {0x4f07938a8c07e9ee, 0x56e45762d943dd47, 0xb3c48ffee367f08f, 0x037c0abf13bb54b7}}},
        {.x = {.limbs = {0xa48bbcf71f86167c, 0x317b23fa350f79dc, 0xad6f0e400a1a959c, 0xd8c0c00badc5e138}}, .y = {.limbs = {0x8c5413fb65165458, 0x9117a04bde169768, 0xdba32df911f6a91f, 0x8a4e4fb7038d6070}}},
        {.x = {.limbs = {0x36d8b419d044bd24, 0x2f3b47013b4e2977, 0x3cd68054d7432e3d, 0x02a1ea133e571a95}}, .y = {.limbs = {0x2ace7645b103ccfc, 0x070da8f43bf78dad, 0x3a26e050b3a10161, 0x0db0b2a21cddfc71}}},
        {.x = {.limbs = {0x9a726035b3a6fccc, 0xfe806d4df2894d6a, 0x88bcb45f18c38b47, 0xb560b33e235b0773}}, .y = {.limbs = {0xcbbf6551d6e5f9e8, 0x40804ea4870f77d0, 0x655a62199d02811e, 0x8df6708f73a10e61}}},
        {.x = {.limbs = {0x2162592f52a01c5d, 0x79d45a495e901a26, 0x4a8ac3f656a949f1, 0x5af0b2c7cd050b2b}}, .y = {.limbs = {0xbed6c8e5df026741, 0xeccf83a888e26c35, 0xee78f4f6ca315bf9, 0xd0cabb103ef1f86e}}},
        {.x = {.limbs = {0x0b3c1747f43922dd, 0xac63ac7224e48ac6, 0x789570d3122410d9, 0x321797a3e9362c82}}, .y = {.limbs = {0x6426e45ca37ba5cc, 0x7f1686318f00afae, 0x92ae02eaa64940e1, 0x2f2d5f0fc5958c54}}},
        {.x = {.limbs = {0x4720e9c27e14e2c8, 0x4a9a5c4ddb48ea55, 0x59d66d12801eedae, 0xef95483192b2a69f}}, .y = {.limbs = {0x75778bf12a856a1b, 0xda45a64aeed33d72, 0x48fe4ee540fd95d2, 0xb7d8c06ee6dccf08}}},
        {.x = {.limbs = {0xf7082dfbe3da292f, 0x07623f94736cb665, 0x6907779326bcfc93, 0x03618191d6dccdcf}}, .y = {.limbs = {0xd289f3d6a2c95aea, 0x4c616d7c057f667b, 0xec0aa6cf7a4a42b0, 0xd0f0ef78b51bec2d}}},
        {.x = {.limbs = {0x4c45674a8097a072, 0x6afa04b405dec19c, 0xcf2905d4ec378a7d, 0x6bf4b50dcd619869}}, .y = {.limbs = {0x3ce0002df92866f4, 0x29bac38a5180b6dd, 0xc5821b2cd8d01bf2, 0x23030d37b66b5b0c}}},
        {.x = {.limbs = {0xe06c1b3a9516a97f, 0xe28d9536867a612a, 0x022850a0d82e62f5, 0xa438b676fcf2237e}}, .y = {.limbs = {0x330352ad6c4091bb, 0x0cb82851943c9380, 0x19153cfcdcd155ec, 0x5d2a50231afa2222}}},
        {.x = {.limbs = {0x5ad2b748ea1a0526, 0xc68bd2c0720a9dc7, 0xde1e413624cecc2b, 0xfba2d68a0cf9eadc}}, .y = {.limbs = {0x8a88d38b1d1488e8, 0xe1031ca78ea83ce4, 0xbf584a933ae7420d, 0x760527a416a9f536}}},
        {.x = {.limbs = {0x5f299e9bc70f3494, 0x2f7bee54b7f94020, 0x7531ed63b8fde6d8, 0x2664fcd8bcdc39c6}}, .y = {.limbs = {0x4ef83f42ffa8c8a4, 0xddce59d55eae1e10, 0x434564466c95457f, 0x270deef40d9ceaac}}},
        {.x = {.limbs = {0xc9fc1ec837b143ef, 0x2b1581dfc9405465, 0x1f0287d4a2765a7b, 0x22da94d0491da122}}, .y = {.limbs = {0xbd490355a1f4e1e9, 0xaa6f106d582ac2df, 0x91fabe0c608dc9af, 0x5a5930b01f459de4}}},
        {.x = {.limbs = {0x122eefb763b1ae90, 0x11f8e6214f8a70e6, 0x3a11ae1a801651f6, 0x1d17b3ae871abaf0}}, .y = {.limbs = {0x406488806554acbb, 0xfbdc70c124cecd57, 0x640907ee9f7ee9a1, 0xf9d83935664099a4}}},
        {.x = {.limbs = {0x7d04535324a74eb8, 0xc000041d285f3d50, 0x72b08d754fd1c352, 0xd1980100bf850344}}, .y = {.limbs = {0xb568fd0d43abda38, 0xcfada34ddae63039, 0x6f00aa15029703f2, 0xcea2c0d9c12ac942}}},
        {.x = {.limbs = {0x0ff88ac61f0acdb2, 0x6222cd89cf35562a, 0x29350cd826360ab3, 0x32f0588dd4bfb83a}}, .y = {.limbs = {0x6967fecbfa2e5d2a, 0x01b6f03018c6f04a, 0xc21daaa539c6140f, 0x4d504437c9749aac}}},
        {.x = {.limbs = {0xb1d8781a266290be, 0x0d38d1e50d11e6e6, 0x071c74e32c4544b5, 0xc2e91568b53cdef5}}, .y = {.limbs = {0xd5f3c5076d99980a, 0xb5445599b834f17e, 0x3d6da92752e2efc0, 0x3e1ff57629dc100c}}},
        {.x = {.limbs = {0xa1a594a4a994892e, 0x4b3e3ac460642368, 0xe4a5fe5a9280f7f1, 0xb60595c235d5ce17}}, .y = {.limbs = {0x8a77303602abface, 0x3a722da52edfdd0d, 0xaacb39b44ee22d9a, 0xa4b899744fd8366a}}},
        {.x = {.limbs = {0x78d17d21ed00b113, 0xbc394e810578790c, 0xc5e6771cdfb516ac, 0x96a35fdeec8f107d}}, .y = {.limbs = {0xf88e3c1357eab421, 0x129a08ee3a004269, 0x9c153535d1a0f801, 0x0ff26c9bb087a082}}},
        {.x = {.limbs = {0xcc4722252af45d38, 0x75e9ee6952049162, 0xdfdb2eacd5eb4d0e, 0xf7712dee24d0588d}}, .y = {.limbs = {0xbe9b7b66d2ee4c80, 0xec1473662115575e, 0xcfd37ed20e34878f, 0x1bc36a578c3cfbef}}},
        {.x = {.limbs = {0x4ab41ead7c206a26, 0x0c34d882645d0d22, 0xad393cc8cdfdc187, 0xeeee8bae04bf455f}}, .y = {.limbs = {0x87ca57a26b14c2a9, 0x2d332583e9e06179, 0xf6d418c3cbe3122a, 0xb95e05bf250636fb}}},
        {.x = {.limbs = {0xec80b8ec537d9370, 0x0b7094d92ea19069, 0xd5ef2820462da59f, 0xeade2d22d7132c86}}, .y = {.limbs = {0x7e856e5b57af1e6f, 0x7dd125419278a42b, 0xb78c393f6372e844, 0x4b4a0d78f782c301}}},
        {.x = {.limbs = {0x90c281ced2db3693, 0x552b03e72849ce9b, 0x19f3afab09e7f65b, 0xe7c17621e806af1e}}, .y = {.limbs = {0x006d1dd3e13bd64a, 0x30849fc24718b1a6, 0x042659e2c1855f2a, 0xac1af46c276d98f3}}},
        {.x = {.limbs = {0x10a9c2f528d14e1e, 0xafee66c0a3637995, 0xb0f68e27f3e6aaad, 0x08b5de12c0ebea08}}, .y = {.limbs = {0x50213fc01eb0f9cb, 0xa9d9fabf616ab5bb, 0x07a56fc3b79e7455, 0x0b8f9c574b6c2eba}}},
        {.x = {.limbs = {0xc60a9e1562f0943f, 0x217823351a90d091, 0xf5f07f1da60ea45f, 0x688d0fccfe354ecc}}, .y = {.limbs = {0x4e4c97ab192c6d66, 0xd1b308203b2381a7, 0x52bea81a88b310ff, 0x8893c0d324340ec3}}},
        {.x = {.limbs = {0x3dff14631dd57292, 0xabe06eedbe28b9cc, 0x31bf8d071645b9b8, 0x17be94981b92c8d0}}, .y = {.limbs = {0x575eea21a5f8e4d1, 0xc48cb34229a50ecc, 0x5eb5c0b5988f0363, 0xe95b4a56cde27a8b}}},
        {.x = {.limbs = {0xb98e04223652a1fe, 0xab4949b0165535b9, 0x0b4301ad10412432, 0x66dc74f1f42749c4}}, .y = {.limbs = {0x271d56887733dce9, 0x5be618f033f0f556, 0x2faa12590bf86d7f, 0x6570ecca88d46bfa}}},
        {.x = {.limbs = {0x466556f9302c6e49, 0xa52ecd6286090687, 0x9d9059230ad52560, 0xe556aae30739c75a}}, .y = {.limbs = {0xf30129e86c492e3e, 0xef2194385d554fdd, 0x67955e973e733a0f, 0x343d314ccd691777}}},
        {.x = {.limbs = {0x031091420599926f, 0x5a999d23ada1755d, 0x727e03d88ea4a784, 0x54f465e4b0253e6c}}, .y = {.limbs = {0x20be2540e134c14d, 0x133370b5f4bd91eb, 0x8fe184671b8b04f7, 0x12b3997eca9dd88d}}},
        {.x = {.limbs = {0x73aadb75137f1a09, 0x63a0cad669b1acac, 0x21f03acaaf3a5971, 0xf8b8cb18a20a13a3}}, .y = {.limbs = {0xa7d04a741dccf533, 0x9bc69549dfe33b14, 0xe2a2198192829289, 0xa59f4a454f22adc0}}},
        {.x = {.limbs = {0x74c744c5a8eb5d28, 0xf7888c9462fad69a, 0xaa341e7083a7ad9b, 0x815cc34b4e8c2de9}}, .y = {.limbs = {0xd8c600bc83893aac, 0xae5bee6620ecc7fb, 0x345214d358cd95a5, 0xf4e8fc85a66b8af0}}},
        {.x = {.limbs = {0x76450135dce8375a, 0x2f2aca8c3c3998f3, 0x31380cd51624d89b, 0x27d25e9d97817e4b}}, .y = {.limbs = {0x9850df129ee6f08a, 0x318676c3ef06ce95, 0x25e5f4f4dfe20f6e, 0xdca6c222c7b79b39}}},
        {.x = {.limbs = {0xb6c11a599920ecee, 0x1e79560f5c5b19e4, 0x82a7de7292d69f74, 0x7c4822ed051aa891}}, .y = {.limbs = {0xf4bf8cfefa096557, 0x8f079b9be579d8e2, 0x948a8f75061c6142, 0x5606e84110c45826}}},
        {.x = {.limbs = {0x1a9f59404c9d6ee7, 0x84de75918f77ce38, 0xd6319c71881700b0, 0xa37e927a6e4c9409}}, .y = {.limbs = {0x6cea78b7010744e2, 0xadab7d4fbff4a396, 0x4fba6879ad8cc1ce, 0x7a765936b90dba8e}}},
        {.x = {.limbs = {0x7b33418ebcae9aaa, 0x37e33557a9ea73be, 0xf816773e7f3fbaf5, 0x28c35b0a0fae4b5c}}, .y = {.limbs = {0x702286eae41f1fcb, 0xfbeaf192d21716b5, 0x323d6c800833bd7f, 0x970cc5fc873b8c15}}},
        {.x = {.limbs = {0xb9c63da51bd350f7, 0x38b9d2083a00a039, 0xd8b2f8ea8e1cfd30, 0xc159f88d7f776a98}}, .y = {.limbs = {0xa8095d3fcb19efdb, 0x93593979d0e6631c, 0x32f0f5e6f871c80a, 0x3564f0350b647de2}}},
        {.x = {.limbs = {0xf8e3fdd0b579184d, 0x51e35439319c0197, 0x677d88baba8d6d14, 0x799fd863c0f6ed34}}, .y = {.limbs = {0xd44fb03d2801167c, 0x57014d8db1ae79dc, 0x4e91a3d8fcb122c9, 0x949e5265f2348129}}},
        {.x = {.limbs = {0x9d1ce2cd912e95a8, 0x46a22d5588f1c9a8, 0x40d6b8a1d73ec5b1, 0x072ecd5a39578e63}}, .y = {.limbs = {0xdacbb84d98f0bb04, 0x5782563baa1229f0, 0x20f0320e99e53d6b, 0xe13568e3e62f4230}}},
        {.x = {.limbs = {0xd89d979498b9fb2e, 0x8a8e8d234bf4595a, 0x7b3f833f49cccd6d, 0xdb4114d67ec61a3b}}, .y = {.limbs = {0x13200ef558081196, 0xd8f669316d6c66d9, 0xfc5f363ccc3eb519, 0xc85f800fd546a62c}}},
        {.x = {.limbs = {0x1168eb72c127ac6e, 0x2f18fc6c27f5f050, 0xebc2a8265c7ec7df, 0x2679c5cc61451316}}, .y = {.limbs = {0xa6c491f984f87d09, 0xb1e67da2d51a1c21, 0xb4d4c077f1d52075, 0xc51c5accb2ff36c7}}},
        {.x = {.limbs = {0x2b585df2fcc42fc7, 0x61d2ef2f3b902020, 0x3cb798c5c460de78, 0x87c574bbce02bd3d}}, .y = {.limbs = {0x3b9940696390a6e3, 0x967316955e3eff33, 0x7ea4af3cbd6d8815, 0x57e3d988e591d247}}},
        {.x = {.limbs = {0xb67d5e7db241bbbf, 0x900448eb50e60918, 0xcda01600a1822bdd, 0x0a746b6886705dc6}}, .y = {.limbs = {0x6353608be9de0cb2, 0x30fea87a4a4080cd, 0x5d3f93efe6951924, 0x074c0b74fd771d13}}},
        {.x = {.limbs = {0x603bdea2b954b9a2, 0x81234ebbd5a18a10, 0x25f57d6b640cd8a6, 0x2467d5648a9bca1c}}, .y = {.limbs = {0xb79b392e48fed7b3, 0xd4cb6c6b0eea0a62, 0xdd7d81d238fc069d, 0xcb5fd9b02ba1b6dd}}},
        {.x = {.limbs = {0xcbaa5341cbe25f1e, 0x1953c33908cfae1d, 0x6d4e416e05fc77cc, 0x35a02f7aff0eee41}}, .y = {.limbs = {0x636144d9efe0c989, 0x5d6241b85af95ad4, 0x767fd6ded52701f1, 0xc17656df0ad297be}}},
        {.x = {.limbs = {0xbb9beaa6eadefa4c, 0xbd1317141ddf24d8, 0x2f42e36868518861, 0x23991abc654f38ee}}, .y = {.limbs = {0x0b3f2c1bc829db1c, 0x2fdf74f6c3db010a, 0x562a7e9961f74832, 0x68a5bdd85fac2cf8}}},
        {.x = {.limbs = {0x03946fac3dd560f6, 0x7f2eb391ed2b2875, 0x2ef720dfe85bd638, 0x7968f3da64d38b4e}}, .y = {.limbs = {0xda2ee0cc0a67f4d4, 0xdcfeb39dff1d5c66, 0xa9335f33e3d322c2, 0x10b4f85e32eda783}}},
        {.x = {.limbs = {0x273dcd867ad654ba, 0xf51db69e5f32d986, 0x4737b28a88874213, 0x85c4a823b3657f13}}, .y = {.limbs = {0xd013d1f3f509d822, 0x81017cf618d49e49, 0x9fb6b207450dc02c, 0xa0ca5f701cdb4a91}}},
        {.x = {.limbs = {0xe18f90f43eac58f7, 0xcf212a45535f6636, 0x1806fc72a5426491, 0x2fb4e46122686296}}, .y = {.limbs = {0x34ad51fdfa338141, 0x7e305660bc5e1173, 0x22e0bd569edaa437, 0x0b52d4926d315b47}}},
        {.x = {.limbs = {0xbb1cc791ef1a0fca, 0xaf33fd74b96a578c, 0x40cef62f53e4a596, 0xe526ae3bafdd5a82}}, .y = {.limbs = {0x591d2068862bda78, 0x145b768acbcf433c, 0x276064dbc55691e7, 0xc2f393887c9e895a}}},
        {.x = {.limbs = {0x5485450751ec1669, 0xa2b4919e0b751eb1, 0x781c3762b14b8fc2, 0xead24668d54ea7af}}, .y = {.limbs = {0x96f44616b752226e, 0x8d49d1804e6d9864, 0x28a1007c8d715faa, 0x23d46eed8f211747}}},
        {.x = {.limbs = {0x88f7843dbaf5d1e1, 0x2a123a290da52157, 0xec4149175095d723, 0x325735da9c1009cd}}, .y = {.limbs = {0xb23e72459088b620, 0x642a3b5e43d58ee3, 0xe1b8b574fee10332, 0xe096a6d01b558075}}},
        {.x = {.limbs = {0xeff7b587fb6bd409, 0xa52735a531246a1f, 0xecc0d0bac617fe1e, 0xbb0dee7a633a4866}}, .y = {.limbs = {0x4af23e5dbb4f06ac, 0xa0e3c6720de7fae0, 0x83896cd11e14f142, 0xf660166502eea1cd}}},
        {.x = {.limbs = {0xc4ccee26c41ea02d, 0x2aad70dae2a1b547, 0xb39cadcc8763ab35, 0xb416f805b08aedf0}}, .y = {.limbs = {0xd8444c9cb8a9a505, 0x12a6e6fed741ccd5, 0xce19c4d24e8b094e, 0x8cc4e0aea020e819}}},
        {.x = {.limbs = {0x4fae8cb6a6482229, 0x2845a19d2a676e6b, 0x8c2a290d0e31c3d7, 0xa36981c85412a36a}}, .y = {.limbs = {0xd9ff945eaf53b545, 0xda6e7cddf637d665, 0xd31bb1ba55ebb14f, 0x717bd18b202a08e3}}},
        {.x = {.limbs = {0x45b32b55a59aed58, 0xa9e0559a3507ef2d, 0x4e7286a3e2cb5e49, 0x1856a2bb3d3521e9}}, .y = {.limbs = {0x6b1f08433b40d522, 0xfbe7c81afc793937, 0xff34658f35c9ae57, 0xafb3864137badba6}}},
        {.x = {.limbs = {0xcd173b713301b6b5, 0x5107b68e338f5830, 0xdb7c27c2dc66b202, 0x37c7279c0d1d5963}}, .y = {.limbs = {0xc7fab925a581ff29, 0xcd43ebc5379478e8, 0x93e3915f68376ee3, 0x9e6256a119b8072f}}},
        {.x = {.limbs = {0x23cbb12b1a7a32f4, 0x75ed1e208b5200c2, 0xe1707d162054717f, 0xd37d07b988c56185}}, .y = {.limbs = {0x2488c77b116cd158, 0x2deb8f4d0a420bfa, 0xcf27eae176c2ddcf, 0x42dc3583000c2768}}},
        {.x = {.limbs = {0xc646db20928a7694, 0xde2263100c69d536, 0xd8aac643b82c69b3, 0x36d71dfe160bd11f}}, .y = {.limbs = {0xe4b2c92cf3601a21, 0xaec23ee4a97a20b7, 0x084c2b5321c06804, 0xa073064832e02390}}},
        {.x = {.limbs = {0xe1424153e8ccdaff, 0x83f018b81b84d2b5, 0x5ccaa869b6fa2796, 0x4eb9db8ad19b3efe}}, .y = {.limbs = {0xfe8a2e986226d446, 0xaef5854988024c31, 0xb0afd5d46995d247, 0xd505efc2a6f0261e}}},
        {.x = {.limbs = {0xe355aac5797da05b, 0x1d0f35bd90da14e0, 0x737f69e326bb143c, 0xd7a177e70e60a6db}}, .y = {.limbs = {0xa5dbaf989136e177, 0xccb5bc55c296fa87, 0x6605c0dd1db4d4dd, 0xedee659fb9881119}}},
        {.x = {.limbs = {0x09400c138587e8bc, 0x6a64de9c52a6e0a6, 0xbb61066c53e3adaf, 0x13389b4d916d8b30}}, .y = {.limbs = {0xc421c2c93315ef83, 0x3dca95231cb482eb, 0xb16e835c28fb7a84, 0x67167bcafd32b065}}},
        {.x = {.limbs = {0xb0e57913dcabe6b9, 0x6a25d5107f363f17, 0xf4b580ff65ff8e49, 0x8b2fffaf4d9dd2ce}}, .y = {.limbs = {0x863cb2ebf5f3cc6d, 0x390a81de4f42b8a4, 0x430dd38863a144d1, 0xd81ce781aa554bb7}}},
        {.x = {.limbs = {0xbe78f0cd4d69ad6e, 0xe6dc7a29b54c6637, 0x541de59d4be862ff, 0xc294ff9490c7d409}}, .y = {.limbs = {0xacca6a353a3edee6, 0xe4144a47c2fba04d, 0xfad6104ff566b8b4, 0x325caf3871246227}}},
        {.x = {.limbs = {0x4f82eacf329dd331, 0x1b7bfefef90cb2aa, 0xa542fa59f51a6667, 0xc3d96ac7e9e207a4}}, .y = {.limbs = {0xae17bda61736d133, 0xad01f7c9d52f9be0, 0xdf840b9317c41a2a, 0x34d7980b1f2b6311}}},
        {.x = {.limbs = {0xd9a3d69212937055, 0x0820f4df9ae4ba4d, 0x803f6f9b3471ddbd, 0xb4e72b874372f19c}}, .y = {.limbs = {0x2a4b1a408d421869, 0x4350e9029e89c05c, 0xc8fa4b0ebe05bab0, 0x287c1dc5e3d59a75}}},
        {.x = {.limbs = {0x45530b36ceacef82, 0x4de65a27831fe184, 0x24baa6dda27cf329, 0xeda00fa5ec3affbc}}, .y = {.limbs = {0x7e92c43520968b2f, 0x8cdaad292cd58757, 0xa15e982da1c18ac5, 0xbee2fc9a32b46bb1}}},
        {.x = {.limbs = {0x93d8f8a9c26dd14d, 0x57cfa9daf3062579, 0x56084dc1e18f722a, 0xf4281818b6603327}}, .y = {.limbs = {0x8d8c46fef938adeb, 0xab17f143b67142f9, 0xcc36e7e737feaa96, 0xc07125d74ff1b1f8}}},
        {.x = {.limbs = {0xb267a454fd11982f, 0x93fe12f24d7ab850, 0x179578d576c27b89, 0xea19daa9bcabd612}}, .y = {.limbs = {0xace3f79d065db1b1, 0xa5a516064e1984ce, 0xc28299b72c75f30d, 0xa43bcdbe22852bdb}}},
        {.x = {.limbs = {0xd136984d70bc8963, 0xda9177440f8ee77c, 0x51b162e37afa74f0, 0x5759a604ae790921}}, .y = {.limbs = {0x89bef129268c943d, 0x78432342ed8e1368, 0xf328fe6d0d374881, 0x07e24ef24be65089}}},
        {.x = {.limbs = {0xfd9d5fc104cb2d23, 0xc31bad703973108f, 0xca838431b1975c49, 0xe72702133a06ee94}}, .y = {.limbs = {0x0baefdbdacb6bdf7, 0x8d585ca5536651c0, 0xfdc34f647900fea7, 0x9d86182008a64626}}},
        {.x = {.limbs = {0xea2608b0c37ce61d, 0x67c47306178d8ac6, 0x9a894589ad43b8dc, 0x63e30dafe8deb050}}, .y = {.limbs = {0x818060fbb011a990, 0x2d98fb669385cae4, 0x230105a312ac93bd, 0x6bb4f64c6225a4cc}}},
        {.x = {.limbs = {0x4f18609cea222a57, 0xc2c1b0154bd638ed, 0xfde8e20769e84f12, 0x2dbd5da9b818d9b9}}, .y = {.limbs = {0xef4a16dcaf65bb58, 0x4c17a5de717cb19a, 0x7290d8fe0c90e663, 0xb8ed7fef5508e035}}},
        {.x = {.limbs = {0x455c45eff234d24f, 0xdd0df01905feb3f7, 0x2a9e318390a7c06e, 0xfbd16a22ef883fe6}}, .y = {.limbs = {0xdd23159884d88855, 0xe92d4328afeb716d, 0x78602da303768fbb, 0xe56288ad74b23aa2}}},
        {.x = {.limbs = {0x1c56814763650123, 0xaadabc5449db949b, 0x1f4b874a7b4d7e95, 0xb965284f0c15f89c}}, .y = {.limbs = {0xf6e4547417700aff, 0x50dfa3cb6c9e22c3, 0xcfa2592104a5e6b8, 0x64d4e067784d1698}}},
        {.x = {.limbs = {0x8b0704dca93dd161, 0xa70498b69e5dd8d5, 0x4cb315540f4fd639, 0xc0f78aa66fd4150e}}, .y = {.limbs = {0x7c260a4fd4d1d843, 0x84f6df4accf71dd5, 0x9edbf0cbbec1ed93, 0x90319c78a7661e92}}},
        {.x = {.limbs = {0x6a5069e351ce29a5, 0xf2ed3e8d8d73cb00, 0x19e8aa9e6d67b165, 0x8fb9f877c31d6d05}}, .y = {.limbs = {0x6ff53ffe572e5160, 0xf4391f21cf4b2744, 0x7ae2e2b635d1d10d, 0x0abf356f1d040263}}},
        {.x = {.limbs = {0x06199d0226907fd4, 0x0b07547ef0208d2e, 0xa8130eba45e44d91, 0x8086e4954064f0cc}}, .y = {.limbs = {0xe3c6e7bb57e2b946, 0xe42eace07eca4b10, 0xf04b4107a3001f5e, 0x0eb86d501bc56e19}}},
        {.x = {.limbs = {0xb81f01c02a2bef17, 0xecb3f8f01e9e5d0d, 0x04f05d70f571090b, 0x71f203d969c3cd79}}, .y = {.limbs = {0x824d544ef2d889a2, 0x98272504d2802950, 0x422ce987bfa3bc17, 0xa81ef3ffbbe42aa6}}},
        {.x = {.limbs = {0x5c0ee8ba0b804e30, 0x1a01ac6ee89f1310, 0x0df51828ba21ce34, 0x09b698a8914ac70e}}, .y = {.limbs = {0xbab454ee91ad7266, 0x9356b85bcba035f6, 0x8b7c3a26af55bc5f, 0x2ce20006004e128f}}},
        {.x = {.limbs = {0x5b8860296b0905f9, 0xb9dcb39e40d9427b, 0xc1f6bf1e5bce4abe, 0xba9068d9ecfd6774}}, .y = {.limbs = {0x22ce9d6941f4cc09, 0x5dd4d26e43c2c2e9, 0x370d33c1dfa214b8, 0x7dc62aea6e4bf29c}}},
        {.x = {.limbs = {0xb191c6f2c30e04f5, 0x085ee25cb7d68d08, 0x7275ca4eb4a923eb, 0x5d7b6b3aa4ac1f47}}, .y = {.limbs = {0xfc892586b8acc636, 0xe2444811ae653ba0, 0x460247476466a84b, 0xcd747e5406cdca1d}}},
        {.x = {.limbs = {0x9e7839d2cc2ae7d0, 0x9367681882fc7713, 0xf75e95b5c7a3923c, 0x0877cb65355ae258}}, .y = {.limbs = {0xb49fee6b7d4c2bde, 0x6f03c5f2f0b19cdb, 0x7a29ba8ef1dd4cb2, 0x9b15e116eef23dc1}}},
        {.x = {.limbs = {0x7630b644ee7b2038, 0xde085e4e8a67bd09, 0xf151fb163c84b186, 0x82ebebbdd7af6d57}}, .y = {.limbs = {0x0b376473ab65c68e, 0x86446027c9baf32f, 0xed5223079660edc4, 0x423288eb244b8ca4}}},
        {.x = {.limbs = {0x62fedd8a1268049b, 0xc7fe3db0d4bfee9e, 0x4f69b9c345717188, 0x5091c155d4b218dc}}, .y = {.limbs = {0x097e6a9adade94a8, 0x1968f75d73f00d24, 0x4da46152cd395f35, 0xe66634cdb0bf6e46}}},
        {.x = {.limbs = {0xd5527761aefdb5c2, 0x0409b482a9404e17, 0xf714ee4db21ae1d0, 0x533b0a7e01c4c3cd}}, .y = {.limbs = {0x7baca8a0de0d78c2, 0xad8f1b1316eb0626, 0x4b709c3b22a14ea0, 0x5dcdc6b6be9abf86}}},
        {.x = {.limbs = {0xa607adc1fdaed325, 0x24781dff13fc972e, 0x6498408fc9ae37f3, 0xe95c34e7f683b107}}, .y = {.limbs = {0x25ae60c652d38d27, 0xb55df3fb71a79759, 0xaaf17006303978b0, 0x6de0fc54148cce4d}}},
        {.x = {.limbs = {0x89ad933a5d2287c8, 0x72debd16306279ed, 0x2184bfb2b49b272f, 0xabfbf644df46b2ab}}, .y = {.limbs = {0x02626e58d2ea3832, 0xd2fa9b37ded97d66, 0x53adf12222ca3c31, 0xed58ef440f17496d}}},
        {.x = {.limbs = {0x5abfa23b7dd295fc, 0x1d04905d2be67f01, 0xbbe4cd927b53b15f, 0x3056174741caa14d}}, .y = {.limbs = {0x5b16d674a941de66, 0x43fab3fd2b1723f4, 0x8dc29182b308dad5, 0x9ffaea1c81e25ca1}}},
        {.x = {.limbs = {0x1c5e631f0d1614ad, 0x0526912fa6af8387, 0x752824099d996e1a, 0xc64dbd719bcd3c3c}}, .y = {.limbs = {0x33a4253b1d8d8b55, 0x2735d066338c0d6f, 0x31f0bd1ad3f945c6, 0x919e420c2f02c5e6}}},
        {.x = {.limbs = {0x75710599ad3b98aa, 0xb968075827b0e0ec, 0xa4ae08dbfd39fccc, 0xce4300dba5bd5fc5}}, .y = {.limbs = {0xcf2793127caf931b, 0x5a8b6210dfbbc0a6, 0xc2b979ed52c6c0b0, 0x8f8d54c63e78c546}}},
        {.x = {.limbs = {0xd941dbc56a99a713, 0x9a3bd25ac058a8cb, 0x0021f729b252e7a6, 0x176d3c5159715bb5}}, .y = {.limbs = {0x0f1250e72757a42d, 0x3522d3c122e1ecad, 0x8d1311d99b1033b9, 0x0694a078d21198a6}}},
        {.x = {.limbs = {0x302689ece1bf992e, 0x58e9d943197e9d25, 0x8878f3627fc93319, 0x81d0f3e20f3d2ce6}}, .y = {.limbs = {0xa83c8ef6f8944451, 0x3bfbc2121c449bcf, 0xff9e9c0dce579a2d, 0xa1af34d3cf570c1a}}},
        {.x = {.limbs = {0x501f3193090d35c0, 0x87f0c11e809ff54d, 0x070299ee139ab88d, 0x4cf90598a58d361f}}, .y = {.limbs = {0x3f8ca4aa6cc5cc0f, 0x168d92f9254a4d5d, 0xb7ed92a3c272a5f7, 0xc62b4fc1d66f6133}}},
        {.x = {.limbs = {0x06bfd1cf39647d93, 0x5f3eea5c0479b303, 0xa24fce015e6a36bc, 0x89633ea617fe37c1}}, .y = {.limbs = {0x9389479636628f12, 0x687dce2e8eb6602c, 0x3176c47a5c4b51fd, 0xd7b7739e074c2bb5}}},
        {.x = {.limbs = {0xb9cf9176f572cfa6, 0x28198aa3ce1ef4d1, 0x9298753e921c90a3, 0xfabf4775d48eae0b}}, .y = {.limbs = {0xce4ee4388f82c89f, 0xa83c51977ec3e695, 0x41fb31fc5f845000, 0xc6a5bb1e826a6a76}}},
        {.x = {.limbs = {0x1fbe22765ffa5f78, 0x2c127dfabc908339, 0xab6c6876ff78ca59, 0x927b70b95da7030d}}, .y = {.limbs = {0x8d6cc4b9c5ae6c10, 0x4ac5051d29525ef8, 0x88e8e0be14f2f1cb, 0xeef0788a0e379f6c}}},
        {.x = {.limbs = {0x032a0d92f7b3db25, 0x59fc53c6009a2d6c, 0x97991a86acf8ba10, 0x720df6c099e2be3c}}, .y = {.limbs = {0x84ffe6f53b18b4af, 0x0c610fdb47b5e213, 0x6dc6ec8164096261, 0x5c40eaff9ddd90f8}}},
        {.x = {.limbs = {0xb576c83701f621ec, 0xa3af418d1e5c10dd, 0x297a549f9fd3e8ff, 0x1ca6bbf4fcc8ba77}}, .y = {.limbs = {0xf055a8081117dddb, 0x2b507234cbc68c59, 0x6e540d0f546ef420, 0xcba9877bdee66671}}},
        {.x = {.limbs = {0x355312a15008ca02, 0x3439592183d1baa3, 0x85b903f80fa78397, 0x9236ab41402e1e05}}, .y = {.limbs = {0x767054de03f4d6d9, 0xfad280d386f0803d, 0x631d73bc68d03cc7, 0x69ac99d95a445bf1}}},
        {.x = {.limbs = {0x4604622d9ae74a02, 0x0993a925805a3dfc, 0x0be2c207ca2d23bb, 0x750a1843a8127d09}}, .y = {.limbs = {0x063d05a1365a3b4d, 0x00bcbccf522f9384, 0xb7e9c9fa5ac5498b, 0x65d77215fafa46c0}}},
        {.x = {.limbs = {0x85922bd0d4736886, 0xfbbce2872eb11be6, 0x05baf1466e5542e4, 0x3f44cd955096cdaf}}, .y = {.limbs = {0x8ba8af9102a2c352, 0x9f3063ba9cf5463c, 0x35e439ed44a6fd18, 0x238bd327f5d8bbf9}}},
        {.x = {.limbs = {0xc6a62458c5e56220, 0x200507f84f7fb957, 0x791add21a87e654b, 0x3d569fa91b4e03a3}}, .y = {.limbs = {0x783f34be21862209, 0x72201990f2cc8275, 0x7f3df15a80845ed1, 0x300bb8286a0f9f9c}}},
        {.x = {.limbs = {0xe8bc940e45d021e7, 0x40abe80d21b73b52, 0x6fb191c021ff10b2, 0xcd60919500886923}}, .y = {.limbs = {0xc58f7d0dd5af3e4f, 0x022001e0724e9c62, 0x49df0178042a5a38, 0x0e1de44955612e23}}},
        {.x = {.limbs = {0x1230748f6a234f65, 0x5ae0e42860653999, 0xbadf401494bd8250, 0xdd805be9c9be85dd}}, .y = {.limbs = {0x297c0275b26c6575, 0x79ae39fc76d8abd5, 0x7675e72ba45dec8c, 0x45e5d1f406d4a16f}}},
        {.x = {.limbs = {0xfb69e8300bdb5fa2, 0xb98a16edbea0738b, 0xc31d055c1f55f771, 0xd21d05a5b3ae139f}}, .y = {.limbs = {0x70bdc45cd0a7bbcd, 0x65b422498848c9f8, 0x3be881ee26546d9e, 0xaab693b48c1b428b}}},
        {.x = {.limbs = {0xf337c23d67a9171b, 0x1575ee7269df7253, 0x93f1e2d49cf542eb, 0x428a4e0840b2f0e0}}, .y = {.limbs = {0x28aa1317a89df469, 0xd8544ed7a22da848, 0x025be6f659f2192e, 0x52f459dc72503b58}}},
        {.x = {.limbs = {0x5573d1ec7c0af81c, 0xd088640ca802b42a, 0x11e02214695a8487, 0x64d97d038270a5ba}}, .y = {.limbs = {0x824375ed6d9597b8, 0xf0c784eb9b22d9df, 0xce173f4c60f16f32, 0xa75868c8d8713c0b}}},
        {.x = {.limbs = {0x87a4d36f5670fba9, 0x10a2498b939f6341, 0x7658fe658f34b4aa, 0xf5dc1668383b4b26}}, .y = {.limbs = {0xea96e304e39c17e0, 0xdd106b0f51e16189, 0x677e8d09cb4ebb20, 0xb46a70f0b2f4e079}}},
        {.x = {.limbs = {0x949d2fa78d6652d4, 0x1ae0a14beaecc822, 0xadf9862a325e5740, 0x55455a489c20eb0d}}, .y = {.limbs = {0x07fae25ac82d6830, 0xb0f5d904e88a358f, 0x462c3aabe602dc0c, 0xef90cbd6cbaeca09}}},
        {.x = {.limbs = {0xe69b087e46e4d393, 0xfc6400ca78341384, 0x0bcddc93eb14f0d0, 0x79d60530b8947dc3}}, .y = {.limbs = {0xc8e66fd68da101cd, 0x52fc1942cdcc506e, 0xe219407903b0de84, 0xacf0ad43d3a35e2b}}},
        {.x = {.limbs = {0xbcca3094d2b71330, 0x84b4d269712548b0, 0x99cd5d7f29fae837, 0x8c2068155ff04a19}}, .y = {.limbs = {0xcf07c09952c79405, 0x239151dffab958b1, 0x1b6c7ca14f53347f, 0xee67065facd6ccca}}},
        {.x = {.limbs = {0x4720a4b8459e07d8, 0x22a2c5c82cb0e154, 0x3f51e1180856daaf, 0x8b5b590b67a16928}}, .y = {.limbs = {0xdb0a851b9c289ee9, 0xe37c6b45bebf7973, 0x9b425409593d5424, 0x9f923bbe75aeb55d}}},
        {.x = {.limbs = {0x2faa6637f04f3436, 0xec63d45f54fab82d, 0xee7b1c3980ba5564, 0x14d24185055e8e69}}, .y = {.limbs = {0x1d57afadf748cdeb, 0xe24c33b82704becc, 0x986cb453d9f8af63, 0x68b6064eaa5bd826}}},
        {.x = {.limbs = {0x9d888ee514524363, 0x3e72fb70693fe2e2, 0x4e550582a246c073, 0x34bf289e44ef19a8}}, .y = {.limbs = {0xeb71a7990a1341d5, 0x8dd204f0e31704e5, 0x403a54c28b28ba99, 0xe6f72818c4421b5f}}},
        {.x = {.limbs = {0x31cfb375cbbfdfe1, 0xd17951855f69ee13, 0xb6ada22d54739ef1, 0xe3164cee083f698e}}, .y = {.limbs = {0x1709c860f2f90792, 0xc24e73fbe895b2bd, 0x8069c4486899c8ff, 0x3fce2621b9058ce5}}},
        {.x = {.limbs = {0x3c0b8c2f453cc9f8, 0xa15389393c77fd37, 0x96e55daea7699c39, 0x6f3fee71dd21f6c1}}, .y = {.limbs = {0xf05304f0941cd00d, 0x5091c2f13b55081e, 0xc1e5198836ad2400, 0x73c7a1e3655dba5b}}},
        {.x = {.limbs = {0x0ef5a308458e7bc1, 0xb2d14fd2a0e8db14, 0x7dfdc6be18b18054, 0xb2db5da2629dbaeb}}, .y = {.limbs = {0xb13c11ce8066739d, 0xf4e9fbaf33e5042a, 0xcc78212eed1ed694, 0x98a41b88d6706186}}},
        {.x = {.limbs = {0x0d3a98d95af08f70, 0xb82bc74ced0451d5, 0xb46be1fcc31bcaa8, 0xb438b1b0d5c13074}}, .y = {.limbs = {0xc491ae2b88032d0c, 0xe36a833ec57890b6, 0x779b3937559f65f4, 0x0e1548170d4f75af}}},
        {.x = {.limbs = {0xb78018a52bb80e23, 0x6609e6055facac74, 0x17d08a86c9c70e4d, 0xfda278a2e69798c2}}, .y = {.limbs = {0x51509c3f17f0da5d, 0x0579f0484b96ed74, 0x320932366875d0f7, 0x1a61bbe9098719e9}}},
        {.x = {.limbs = {0xf82848abd286744e, 0xb9ccb490f208fd90, 0xa5b783239a38327a, 0xc0b31747e247ad45}}, .y = {.limbs = {0xacb96144fd31d40d, 0x14d1d7f6249b90d3, 0x6cf068811da397c4, 0xb6269f6ce3c9100f}}},
        {.x = {.limbs = {0xe32088c91c8b6b3e, 0x9080ffd49b999584, 0x1ff648fe5f5376c7, 0x37c88fd8046e79a3}}, .y = {.limbs = {0xf8a28c0881af4df8, 0x280b521e2b5e8035, 0x3f1e68ff0be43459, 0xf02032a01debf614}}},
        {.x = {.limbs = {0xf38573bf3751e50b, 0x1c408b5142f34206, 0x2172aff3d793fbcb, 0x74e5e00253f4b2c8}}, .y = {.limbs = {0x390e6c2fc6b4b235, 0xdfd40ce44a54ce5a, 0x3e72fb769a201933, 0x5455a58929da1cc2}}},
        {.x = {.limbs = {0x5323b6aead471495, 0x031b4ce872601afd, 0x6608297673c6293f, 0x59ee1a166cb5c9bc}}, .y = {.limbs = {0xe9e5cf446ccdcab7, 0x1c2f050a94c5975d, 0xede0aa526a85e3d8, 0x85526d241df67b81}}},
        {.x = {.limbs = {0xeb6292abb5250ff5, 0x72119b000d9a7811, 0xcd94308893f5efe7, 0x8152c2345f43d594}}, .y = {.limbs = {0x439669f02d6e8e8c, 0x679a82c66bce4b3e, 0x569ce2bfd8fc33bc, 0x812f3c11a1446edd}}},
        {.x = {.limbs = {0x1fee9bb13f9d3e83, 0x78ad0591e5930d04, 0x3c7226cad29a3aa7, 0x88ff17979ddca799}}, .y = {.limbs = {0x3ab59b8f6a46eb44, 0x7e761c36d7dba091, 0xa6b07db572b85566, 0xff9e9fac731e12d6}}},
        {.x = {.limbs = {0xfda7b8896ce90fc6, 0x419afca0bff28ced, 0xb64745664c13d0f1, 0x7a561f46ad34c9ac}}, .y = {.limbs = {0x756bf6498908851a, 0x70567063ef048385, 0x5eed5cff989c39f8, 0x668d872b05d59477}}},
        {.x = {.limbs = {0x56cf7377c4bd8a12, 0x2aebff65aff98b14, 0x5b0c19bf459a3465, 0x45f0e802d722706c}}, .y = {.limbs = {0x99d0e08526af7cc8, 0xf98449d898076a01, 0xf0835bb12ff36669, 0x5d50df92fe85fc82}}},
        {.x = {.limbs = {0x271e02c66657a40e, 0x0a61a80338e82e4f, 0xe621493ccd2744a0, 0x4a2fc89d930e19f5}}, .y = {.limbs = {0xe0e3f2d729d64913, 0x4811dfac3882bfb0, 0xb7f6d28c42cef611, 0xe34e2df333790a4e}}},
        {.x = {.limbs = {0x704ee9b0d35f21a3, 0xa8ea1aeb29c88388, 0x82b1f38962665ec5, 0x6c478753bdde7617}}, .y = {.limbs = {0x9edc58fe17d69d73, 0x2d0136020756f4f5, 0x64ebb121c5f4b207, 0x85683ee2ce2b6193}}},
        {.x = {.limbs = {0xbcff1327c2cf5196, 0xd9ae2acd662f0215, 0x65b9dacd5d8f9da0, 0x3e0af784a2748eb1}}, .y = {.limbs = {0x5f86489fe0dbd503, 0xb4a3ab4fac5b864b, 0x13397b48f47d8ce7, 0x20dff0fc27a5da5e}}},
        {.x = {.limbs = {0x6ceb7b029fc56289, 0x06846fb986db2ac5, 0x946087357d2f5125, 0xd48dd0e72b9e15fe}}, .y = {.limbs = {0x5e28e52b59252043, 0xe81c8cc6a1bca70f, 0xb47880fbfd893563, 0x40e58f1538fe09a4}}},
        {.x = {.limbs = {0xad075ba7f805f786, 0xb32d30a5b651854d, 0xeb6e835804946258, 0x3ead8777e9643084}}, .y = {.limbs = {0x7344e96a96935286, 0xd086deede6917699, 0x62d4b517e3f062e2, 0x6f743a165decd6c9}}},
        {.x = {.limbs = {0x77c28954621e6d7e, 0x0f531b639ed0f01a, 0x7471bde9f6322842, 0x34865cf0788f8990}}, .y = {.limbs = {0x87cfaf6e9bfbfc42, 0x52318f1d82663c70, 0x7b4b503040b6f1c1, 0x294c8794ee545cc4}}},
        {.x = {.limbs = {0x64a6df1d3ced36a5, 0xcf1b8b75687356cd, 0xe467bc2c76998cd0, 0x36ce3d1de64acf0e}}, .y = {.limbs = {0x408570b1726d46f4, 0xa9d9862c52297692, 0xd6e90444a48e928d, 0x412bbce49bb4b29e}}},
        {.x = {.limbs = {0x8cab346317fb8541, 0x5713481fb10acb56, 0x4ee37de3b823d8de, 0x8f469cac6f73be8d}}, .y = {.limbs = {0x66a644e9def76eab, 0x575b276e3d727677, 0x98d97390cdd1dc9e, 0xbd1e8ac31bee9cd7}}},
        {.x = {.limbs = {0x45aae613b789b6c7, 0xbf292868250551d8, 0xae660cd9dd2a25ce, 0xde28f9a5072233bc}}, .y = {.limbs = {0xdf106fc3230b1199, 0xb5dc3b088d953c78, 0xd043059b2e1657ec, 0xfd44fe88fd8d354b}}},
        {.x = {.limbs = {0x7d67b5bb6036e01f, 0x544ae14e991d0542, 0x45fb657f3a96470d, 0x9157725122667198}}, .y = {.limbs = {0x86cd760df84e0454, 0xfdb63e80db2a273a, 0xb72f89bc73fbd6af, 0x601c20035395ce29}}},
        {.x = {.limbs = {0xcc7667d2a5f77acb, 0xa6e04ff0915758ca, 0x39a09cac178d7fb8, 0x95951bd26c67804e}}, .y = {.limbs = {0xfb5929a580fd0eec, 0xf9523b41798b3985, 0x69541a51c3c1097f, 0x2e2679ee526a8036}}},
        {.x = {.limbs = {0xd7f49627eebc9620, 0xad1b815bbb5645e4, 0xcfd34c070f6abca9, 0x6a43c4c63e27dbdb}}, .y = {.limbs = {0xa40a9f688f7e894f, 0x30c7e531bd27bc71, 0xc98a401dfd4e9a16, 0x00af40ddef5e43df}}},
        {.x = {.limbs = {0xe2f828b26d1505c1, 0x3709c3ee046528ef, 0x95198becd6a9611b, 0xf724b92b7e95a3fa}}, .y = {.limbs = {0xbf2ee23f9edf180b, 0x0c94333f263f51d0, 0x5a153303e263a6e5, 0x0181b8544bfde6b2}}},
        {.x = {.limbs = {0xf980b20296425e2d, 0x1fa263ae8ba2a630, 0xb7388ff04ffa223d, 0xa725f78b6720d5b2}}, .y = {.limbs = {0xed49b28f7049742c, 0x87cd0912aff25f34, 0x375199b3966ca58a, 0xc2b00315f1255007}}},
        {.x = {.limbs = {0x02820d8fd0558c4a, 0x07e78abb1b1173b4, 0x07db64e7a5792494, 0x7e345a2369799399}}, .y = {.limbs = {0x0715f6483fdbc32f, 0xc1cd41fc6eb11e1c, 0x02ff6a7abe876d4b, 0x8eb2eaba8f810906}}},
        {.x = {.limbs = {0xbad5f8c3d991d963, 0x4ed1f129045aae46, 0xae01e81ebb4a676a, 0x12da67fa41b38292}}, .y = {.limbs = {0xb483abf471c6ce03, 0xbd54061a7f432a42, 0xa73d59c851352844, 0x56003c75f3795720}}},
        {.x = {.limbs = {0x2bc3891245bee27a, 0xfda0da6f30cf20c7, 0xde001bb8b2022905, 0xd603442dfa7bbcd9}}, .y = {.limbs = {0xd23443d1b414f923, 0x3d237a74704dd283, 0x17f186a88f487d86, 0xf967122751dd92b9}}},
        {.x = {.limbs = {0x4f6b1a5ea9b52485, 0xdb8d33a607ca9f2d, 0x3ad8ad9d1e250336, 0x890b59e7607af021}}, .y = {.limbs = {0xaef67fea0b924fa7, 0xb5cdab3a4cc4e9fb, 0x80fc4b71312a91cd, 0xd30dde1f6d1b44ba}}},
        {.x = {.limbs = {0x640b6ff781009d64, 0x1b61e14e683c1612, 0xa77e4484b4c77ca5, 0x48cee8aece53a54c}}, .y = {.limbs = {0x32df090cdd706d03, 0xc435bddcd5be62a3, 0x5b05c31697f7c457, 0xc1453db37a343879}}},
        {.x = {.limbs = {0xe0612edd98e2a3f6, 0xf3222684a33b5fc5, 0xc04c1e0afe499895, 0x46a89081c092e05c}}, .y = {.limbs = {0x06a19c084b167487, 0xdb60170fe416d933, 0x4417620429ee3004, 0x3f1ad273fc1bc4d5}}},
        {.x = {.limbs = {0x5b99755eb6f0500a, 0x9568e410019841eb, 0xa2ee8c1a24bd4d3e, 0xf322826debfea667}}, .y = {.limbs = {0x4ffb9e391c08c63a, 0xc456e3398335d4fc, 0x1ae84ef012b2b333, 0x692c70595a9ca08b}}},
        {.x = {.limbs = {0xb584b6ea52c123f3, 0x6aef5d9b87623bb3, 0xfcd935f882e7ff0f, 0x9cdb629e43b6cf21}}, .y = {.limbs = {0xe844a541d99b325e, 0x9605fe1f8bfc54d5, 0x85c400c44e0d4d6e, 0x80e432e0f83aac35}}},
        {.x = {.limbs = {0x34778a1e2cc838a0, 0x7da514e954110ea0, 0x6a391e41c6ed5e54, 0x633ffe4f65c1b6a8}}, .y = {.limbs = {0xfeb287778385af1a, 0xd9826666184e006e, 0x69fe61d42c9712a6, 0x7e99861d1c5adf89}}},
        {.x = {.limbs = {0x786d7db4390d1ee5, 0xd803ab31f64160b4, 0xf2966e35ecd8235a, 0x01bdf66d320f9a47}}, .y = {.limbs = {0xbe91b23406bddc9d, 0x3ebc1e0f5af4b5da, 0x2976e9c49daf5837, 0xa7af21a87bc7334d}}},
        {.x = {.limbs = {0x764fce5209c182ff, 0x28269f9cdcf192a0, 0x587f94d898ec5b77, 0x4f19938fc19a8a7e}}, .y = {.limbs = {0xe9a34348c7a2acca, 0x8be53b87d6fa76c6, 0x550aad08d437c658, 0x34654a1b2e018311}}},
        {.x = {.limbs = {0x67081c938cc68e8a, 0x3dad171f32989d20, 0xb3abc5a22ac46ed3, 0x50c5b630b0f2f536}}, .y = {.limbs = {0xe91a9518b0b1dc3d, 0x3a8c11875675b175, 0xefe92f843c27f4ea, 0x34a79b862e934042}}},
        {.x = {.limbs = {0xdb59f10e8e7e2796, 0x2c5bf6aa19915236, 0xf8af0e798d2435d4, 0x808eacf7d188c518}}, .y = {.limbs = {0x0132e41a45c5066b, 0x38470e43739a8f06, 0xca93ab45e18e7ec2, 0x3b81b08db80358bb}}},
        {.x = {.limbs = {0x01921bcc4d2788f5, 0xd8e5e58729679a7a, 0xfa8252f57b2ce15b, 0xba61ab8865539df6}}, .y = {.limbs = {0x7550cefce00f6d1b, 0xb5e3604c8feecbfa, 0x0ab5873083cf4c72, 0xad4bfc1439ff35c7}}},
        {.x = {.limbs = {0x94b2acb4d2612751, 0x7bcec156ac413060, 0x141a5df0933e4ad7, 0x6fc41a9a0a10c390}}, .y = {.limbs = {0x022efdab4ee5bff2, 0x4e48206e07fc0be1, 0xc8c4958359ad12a3, 0xf403ff393e47434c}}},
        {.x = {.limbs = {0x42c11fcc0833fc33, 0xa2bebf1c93db6510, 0x8adc2234af285ccb, 0x6a6bbc1345446c00}}, .y = {.limbs = {0x9e1aecef18202b59, 0x2edc4b7f111be0ec, 0xcd4bee73341319a6, 0xc8546e450811bc02}}},
        {.x = {.limbs = {0x8f53190a92603067, 0x5e7bfc79eb60affd, 0xe19253992e9557eb, 0x5c3ba92cb40ace87}}, .y = {.limbs = {0x728128bba9c29d7e, 0x5c0cf2fb63adc26b, 0x84acf85ddd69a5dd, 0x55e3ae335e83ae26}}},
        {.x = {.limbs = {0x50df00819911a508, 0xd29aa637eba0cc90, 0x17ef7b87e90c82bb, 0x61ac02895f506058}}, .y = {.limbs = {0xa33c98715472e27a, 0x6565f3f1fa487987, 0x62d5212bf395f7a4, 0xc633081669933943}}},
        {.x = {.limbs = {0x33eaf9a88952b0b4, 0x7a6609b578d814bb, 0x191725a70b157e1f, 0xf1c03797383d2579}}, .y = {.limbs = {0xb5027210bde70699, 0x6e9c433148cc1290, 0x1d1956143848811a, 0x14ef3432c63dd51d}}},
        {.x = {.limbs = {0xe810826e6b5db5c7, 0x2d0e1eab05076399, 0x645616c84ca93e5b, 0x83f74a78f919a605}}, .y = {.limbs = {0x11eddbf5f0288cd4, 0x911a11ebf16f5b83, 0xc032697e37ba05c9, 0x062ffddd012633cd}}},
        {.x = {.limbs = {0x50a3ae2e34779284, 0x0702c88181f3fb6b, 0x96a481e9b798aba3, 0x2a084128f4035078}}, .y = {.limbs = {0x66f340ab76df5333, 0x412ab74f9435433f, 0x849cef67e700e068, 0x98569421b780e26a}}},
        {.x = {.limbs = {0x4265c87e7316c4b4, 0x72f3e6c19d4f93b7, 0x52c6f7a4dadf7e71, 0x87c590373262687a}}, .y = {.limbs = {0xd2cd0ab1031716b0, 0x23b8574b9837875f, 0xb315247841619420, 0x4fdbaff43269ef81}}},
        {.x = {.limbs = {0x18a89a4d51af7d3e, 0xa8eb0ff67c8a51a7, 0x2a7a4483bee5839c, 0xe8e48862ff1169f6}}, .y = {.limbs = {0xd1d08eae299a9f73, 0x7d05d03874b765c5, 0xbc37c03b188a6fbe, 0x155e21d762dbfa24}}},
        {.x = {.limbs = {0xdce6f7c660191161, 0x35d0a824439de51f, 0x6167807b6a15e422, 0xd0205700ffb85120}}, .y = {.limbs = {0x3d4a3705fbf6c8ce, 0x206f12cd5a3449df, 0x09c25e946dc08ded, 0x12d4858cc1033c65}}},
        {.x = {.limbs = {0x5da375931ebf15b5, 0x10372dcbdb48a35d, 0xabfeb253abffb00c, 0x9b12e56e36ba7177}}, .y = {.limbs = {0xc6d39db228dbc4cc, 0x098357d4c67c2411, 0xe339ff767faa5505, 0x63fa907b77b0ad60}}},
        {.x = {.limbs = {0xd5e7cf1638946c45, 0x0492d6f558d53844, 0x4af9f4bc1565209a, 0x949957b1b3ae832c}}, .y = {.limbs = {0xfd0f4e9f280fc769, 0xc3efeabdc36bfd9c, 0x053bba57af7e16a5, 0xbb6b6ba22a03d0d6}}},
        {.x = {.limbs = {0x1e7982f53739b56c, 0x28b34e14dde5e8e3, 0x6cdad0f670c9dcc7, 0x87d9e9fb284de91f}}, .y = {.limbs = {0xc3f189cd2a033081, 0xf872ee410c16ff7c, 0xc54c271e840ce6eb, 0x38ecaad0fd8e2f53}}},
        {.x = {.limbs = {0xfd3b5145a1f8da5b, 0x7964f5abdb545a8f, 0x62a79720e97e628f, 0xf7d9306ce5e270fe}}, .y = {.limbs = {0xe128f660e9a1f1e9, 0xa54becb8c06a4b74, 0xd04b38e526e2d0ae, 0xdf673c3881048ce6}}},
        {.x = {.limbs = {0xa4c1e92830cce054, 0x55555066b74f75c3, 0xa9cf904dec49c4ec, 0xfcdea32e471cd01c}}, .y = {.limbs = {0xdd5282797d9a9077, 0xecc7ec52dc4838ce, 0x8566da72c141c14c, 0xf29e49ca8ce76559}}},
        {.x = {.limbs = {0x5337544fdeb5a8a5, 0x6b7cdf1b8db66b99, 0x01071ab6fff133ec, 0x06d1360dfe8e14d0}}, .y = {.limbs = {0x1ec3863b84041799, 0xfde5a6f2ade574c9, 0xbd75ceea56e88cfe, 0xd73bba043d9277d6}}},
        {.x = {.limbs = {0xe60d0dfdae6a10bc, 0x803185e287d9bfc5, 0xfb16789fc4cc53e9, 0x11c3b7cff9fffa5d}}, .y = {.limbs = {0xd1a3c44a786b8397, 0x9d19a4647af35909, 0xf55697a7d4f01f36, 0x30b5c3127b1854c1}}},
        {.x = {.limbs = {0xc6348a529bb8e9c5, 0x8c9b84edf6087167, 0xe5aa295fd9a791d0, 0x639eede9dd4d5f1c}}, .y = {.limbs = {0xa04646fba10547f0, 0x61d35ed6ec8d5a7d, 0x4a4fcdac40a8e402, 0x9cb34757a19509b6}}},
        {.x = {.limbs = {0xcf35c90b7fd22386, 0x35269d92372684d6, 0xe8163144717efdbe, 0x844d2bfff3426e5a}}, .y = {.limbs = {0x10e99146b3d8b895, 0xcedcef94facf0343, 0xaf9394876d138ebd, 0x62a2f64e82ed2b3c}}},
        {.x = {.limbs = {0x59ddec2aa2499123, 0x43a948984ba3459b, 0x4227928307bcfa00, 0x25dec82bb1533b97}}, .y = {.limbs = {0x60de4737ec567322, 0xbebc6ed033b6b182, 0x38945f3b833f3965, 0x0998887ce48c9389}}},
        {.x = {.limbs = {0xfbc9874d1d3405d6, 0x30452c181683b2a9, 0xb99fb78ad500e21a, 0xa909a48bb03a0d23}}, .y = {.limbs = {0xb6f932f3c77f6d60, 0xca294c560964b844, 0xc981839594ccaeed, 0xde93358d4ea3431b}}},
        {.x = {.limbs = {0xebba4d6653b36a6d, 0x6c586faf32afe0f2, 0x1b29acd2259c87dc, 0xc8f3bf149e208114}}, .y = {.limbs = {0x900fbfd9b063a7f5, 0x81f36c9d4a0d9710, 0xc030b6faa37138ac, 0x8fff389fb1696816}}},
        {.x = {.limbs = {0x5de8650898c491f9, 0xa3d4459fe03010ad, 0xb85ef16988e319d2, 0x191c60906ab835a9}}, .y = {.limbs = {0xfe5ed687c76d4ea5, 0xc97e4c99efd24452, 0x033a1c66b13f3ca6, 0xf92fa57793ae1f28}}},
        {.x = {.limbs = {0xdada583b5245dfd0, 0x09586d8d813e0018, 0x5036a7ae49e86efc, 0x8e9d290a5668fa53}}, .y = {.limbs = {0x391d7bcb93db790e, 0x18e887edfde46c27, 0xfbe05c3d66f9309b, 0xcaf699d7b6a3f6dd}}},
        {.x = {.limbs = {0xbecbed532f8bf8ce, 0x683bca682a5a79d0, 0x528c8090ba572f3f, 0x2efd0bc4f9957e79}}, .y = {.limbs = {0x44883ede6ebc587c, 0x41b6eab77f74b30c, 0xeb3dcf081d3d589b, 0x7636726fa2730110}}},
        {.x = {.limbs = {0x7c7dba650797d16b, 0xaee3610e2e79f542, 0x73e35829f7780ae3, 0x0198dcc2dd4363e1}}, .y = {.limbs = {0x184a5dba7026cbb0, 0x796f810d46208a2b, 0xd9f074515b1891a9, 0xfb0d1ebee9b02173}}},
        {.x = {.limbs = {0xfccfb6bf0c712830, 0x9cb4e2564dcb3bbf, 0x126272d1e831fa0f, 0xb0a5ada485462d82}}, .y = {.limbs = {0x4d95b19a2256fa6d, 0x87453e68d209d679, 0xa7231eaa0467ca92, 0x2ab11ca3cb953093}}},
        {.x = {.limbs = {0x2dbcf2f237394647, 0x170b17e66d7d26dd, 0x53fe1204758d38e7, 0xa8656082c48da86c}}, .y = {.limbs = {0x01c9a6707ad9e9a0, 0x41add14e09976d20, 0x1c49d1b92e4b9562, 0x44495e2ae3aedc74}}},
        {.x = {.limbs = {0x61603f848f73f9ed, 0xca621223908180fd, 0x579001b9db1edb7c, 0x4de3f6e573b26423}}, .y = {.limbs = {0x59f6c2655201a805, 0x891562354f648f4e, 0x12449da8b76b2884, 0x5d397f6c45df6ddb}}},
        {.x = {.limbs = {0x55054519d328141e, 0xefbb8a4903e060f4, 0xc4e533d104326ac6, 0x0432a63a3897d813}}, .y = {.limbs = {0x1b075bc6c1d3fc5d, 0xbd899c6f6e17847f, 0x89c295df5980aad1, 0xe44c01287a6d185b}}},
        {.x = {.limbs = {0x34b0f47a99d40da8, 0xd2229eb66f82a347, 0x0fcb706ed4b5b587, 0xbd15eb1dbc0ed0fe}}, .y = {.limbs = {0x48442f145d6d2cd6, 0xcb2d35277c1307ac, 0xb860fe70c59501b0, 0xeededf79ac78cca3}}},
        {.x = {.limbs = {0x05a51634a859351e, 0x6d132e992f8083b6, 0xeb427a9274f1864a, 0x41984dea4a1333d8}}, .y = {.limbs = {0xe1781f765822eb5d, 0x1ade5356db8e68ff, 0x9c32c46ab5bb6a71, 0x891d982c59e61dad}}},
        {.x = {.limbs = {0xac8fcefcee4b82fe, 0x601c266645dce7b1, 0x15a6ff94fdd18746, 0x8ee134a7288f5fd4}}, .y = {.limbs = {0x2badb9e328741223, 0x3f62dc1c6c2a80b8, 0x3c0a837662b5d3a3, 0xd7ba00301b022a5b}}},
        {.x = {.limbs = {0x5332b83c4246dbf7, 0x8b08f883e8122a2d, 0x9ac25b90ffee6043, 0x471bcfa7d2d1aae8}}, .y = {.limbs = {0xeb1c27ed191fae8b, 0xe437d49acefb7a41, 0x6b384f4125bca487, 0x8e9191e33432aed7}}},
        {.x = {.limbs = {0xb3128d4d40fe779a, 0x08c7df9ce969ea33, 0x03eeb647c8c0c513, 0x1d320dff7dc30a00}}, .y = {.limbs = {0x0d84bf630e0eb14c, 0x6fb039f55715323f, 0xec2b3afb2b008270, 0x27add1b19472c1e5}}},
        {.x = {.limbs = {0x499ba5948833594b, 0x002fdd5cb1416319, 0x259664b0794c9ac7, 0xc840909b90eaea72}}, .y = {.limbs = {0x209302e10bad6897, 0x276c4a15ce32fe09, 0x458e76393023d9e8, 0x30e42d151f8ed0cf}}},
        {.x = {.limbs = {0xe10d2ee3a3b33d77, 0x880413e718d06f68, 0x9717f374a4454bf6, 0x62d254fb0688513e}}, .y = {.limbs = {0xfbd2553d1347e866, 0x0bd4f747a424e92c, 0x5be695b524b94323, 0x382b1ba5bc4fa6b2}}},
        {.x = {.limbs = {0x26d65f7252841192, 0x6f1ebab3e09549de, 0xfd0cffcc742d4254, 0x7aa8d567e1d473c2}}, .y = {.limbs = {0x434787bf03e4e0eb, 0xa18b1737f41c0b6a, 0x678e932ed7a43b8a, 0x38ac6c58aefb6167}}},

    };

    JacobianPoint jacobian_result_point;
    JacobianPoint tmp_point;

    unsigned long long limb;

    unsigned long long is_not_first_non_zero_window = 0;

    unsigned long long mask_use_g_times_window = 0;        // we do not had a non-zero window yet - this window can be zero or not
    unsigned long long mask_sum_g_times_window = 0;        // window is not zero and this is not the first non-zero window
    unsigned long long mask_do_not_sum_g_times_window = 0; // window is zero and is not the first non-zero window

    for (unsigned char limb_index = 0; limb_index < 4; ++limb_index)
    {
        limb = scalar->limbs[limb_index];
        for (unsigned char i = 0; i < 8; ++i)
        {
            jacobian_montgomery_double_point(&jacobian_result_point, &tmp_point);
            jacobian_montgomery_double_point(&tmp_point, &jacobian_result_point);
            jacobian_montgomery_double_point(&jacobian_result_point, &tmp_point);
            jacobian_montgomery_double_point(&tmp_point, &jacobian_result_point);
            jacobian_montgomery_double_point(&jacobian_result_point, &tmp_point);
            jacobian_montgomery_double_point(&tmp_point, &jacobian_result_point);
            jacobian_montgomery_double_point(&jacobian_result_point, &tmp_point);
            jacobian_montgomery_double_point(&tmp_point, &jacobian_result_point);

            unsigned long long window = limb >> 56;
            unsigned long long window_is_not_zero = !!window; // bool

            mask_use_g_times_window = -(!is_not_first_non_zero_window);                                                     // mask
            mask_sum_g_times_window = -(window_is_not_zero & is_not_first_non_zero_window);                                 // mask
            mask_do_not_sum_g_times_window = -(((unsigned long long)(!window_is_not_zero)) & is_not_first_non_zero_window); // mask

            is_not_first_non_zero_window = is_not_first_non_zero_window | window_is_not_zero;

            jacobian_point_addition_jacobian_montgomery_plus_affine_montgomery(&jacobian_result_point, &g_times[window], &tmp_point);

            jacobian_result_point.x.limbs[0] = (g_times[window].x.limbs[0] & mask_use_g_times_window) | (tmp_point.x.limbs[0] & mask_sum_g_times_window) | (jacobian_result_point.x.limbs[0] & mask_do_not_sum_g_times_window);
            jacobian_result_point.y.limbs[0] = (g_times[window].y.limbs[0] & mask_use_g_times_window) | (tmp_point.y.limbs[0] & mask_sum_g_times_window) | (jacobian_result_point.y.limbs[0] & mask_do_not_sum_g_times_window);
            jacobian_result_point.z.limbs[0] = (tmp_point.z.limbs[0] & mask_sum_g_times_window) | (jacobian_result_point.z.limbs[0] & mask_do_not_sum_g_times_window);

            jacobian_result_point.x.limbs[1] = (g_times[window].x.limbs[1] & mask_use_g_times_window) | (tmp_point.x.limbs[1] & mask_sum_g_times_window) | (jacobian_result_point.x.limbs[1] & mask_do_not_sum_g_times_window);
            jacobian_result_point.y.limbs[1] = (g_times[window].y.limbs[1] & mask_use_g_times_window) | (tmp_point.y.limbs[1] & mask_sum_g_times_window) | (jacobian_result_point.y.limbs[1] & mask_do_not_sum_g_times_window);
            jacobian_result_point.z.limbs[1] = (tmp_point.z.limbs[1] & mask_sum_g_times_window) | (jacobian_result_point.z.limbs[1] & mask_do_not_sum_g_times_window);

            jacobian_result_point.x.limbs[2] = (g_times[window].x.limbs[2] & mask_use_g_times_window) | (tmp_point.x.limbs[2] & mask_sum_g_times_window) | (jacobian_result_point.x.limbs[2] & mask_do_not_sum_g_times_window);
            jacobian_result_point.y.limbs[2] = (g_times[window].y.limbs[2] & mask_use_g_times_window) | (tmp_point.y.limbs[2] & mask_sum_g_times_window) | (jacobian_result_point.y.limbs[2] & mask_do_not_sum_g_times_window);
            jacobian_result_point.z.limbs[2] = (tmp_point.z.limbs[2] & mask_sum_g_times_window) | (jacobian_result_point.z.limbs[2] & mask_do_not_sum_g_times_window);

            jacobian_result_point.x.limbs[3] = (g_times[window].x.limbs[3] & mask_use_g_times_window) | (tmp_point.x.limbs[3] & mask_sum_g_times_window) | (jacobian_result_point.x.limbs[3] & mask_do_not_sum_g_times_window);
            jacobian_result_point.y.limbs[3] = (g_times[window].y.limbs[3] & mask_use_g_times_window) | (tmp_point.y.limbs[3] & mask_sum_g_times_window) | (jacobian_result_point.y.limbs[3] & mask_do_not_sum_g_times_window);
            jacobian_result_point.z.limbs[3] = (ONE_IN_MONTGOMERY_3 & mask_use_g_times_window) | (tmp_point.z.limbs[3] & mask_sum_g_times_window) | (jacobian_result_point.z.limbs[3] & mask_do_not_sum_g_times_window);

            limb <<= 8;
        }
    }

    jacobian_montgomery_to_affine(&jacobian_result_point, result_point);
}

inline void g_times_scalar(const Uint256 *scalar, Point *result_point)
{
    g_times_scalar_antigo(scalar, result_point);
    // g_times_scalar_novo(scalar, result_point);
}