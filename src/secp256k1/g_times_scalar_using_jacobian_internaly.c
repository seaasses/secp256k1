#include "constants/secp256k1.h"
#include "secp256k1/g_times_scalar_using_jacobian_internaly.h"
#include "secp256k1/jacobian_double_point.h"
#include "secp256k1/jacobian_point_addition_jacobian_plus_affine.h"
#include "secp256k1/jacobian_to_affine.h"
#include <stdio.h>
inline void g_times_scalar_using_jacobian_internaly(const Uint256 *scalar, Point *result_point)
{

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

#pragma unroll
    for (unsigned char limb_index = 0; limb_index < 4; ++limb_index)
    {
        limb = scalar->limbs[limb_index];
#pragma unroll
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

            jacobian_point_addition_jacobian_plus_affine(&jacobian_result_point, &g_times[window], &tmp_point);

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
