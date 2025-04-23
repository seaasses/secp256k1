#include "constants/secp256k1.h"
#include "constants/montgomery.h"
#include "secp256k1/g_times_scalar.h"
#include "secp256k1/jacobian_montgomery_double_point.h"
#include "secp256k1/jacobian_point_addition_jacobian_montgomery_plus_affine_montgomery.h"
#include "secp256k1/jacobian_montgomery_to_affine.h"
#include <stdio.h>
inline void g_times_scalar(const Uint256 *scalar, Point *result_point)
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