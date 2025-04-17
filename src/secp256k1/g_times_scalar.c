#include "constants/secp256k1.h"
#include "secp256k1/g_times_scalar.h"
#include "secp256k1/double_point.h"
#include "secp256k1/point_addition.h"
#include <stdio.h>

inline void g_times_scalar(const Uint256 *scalar, Point *result_point)
{
    // this does not work for scalar = 0. We do not have a way to represent the point at infinity
    const Point g = SECP256K1_G;
    Point tmp_point;

    unsigned long long is_not_first_bit_set = 0;
    unsigned long long limb;
    unsigned long long use_g;
    unsigned long long use_double;
    unsigned long long use_double_and_sum_g;

#pragma unroll
    for (unsigned char limb_index = 0; limb_index < 4; ++limb_index)
    {
        limb = scalar->limbs[limb_index];
#pragma unroll
        for (unsigned char bit_pos = 63; bit_pos != 0xFF; --bit_pos)
        {
            use_g = ((limb >> bit_pos) & 1ULL);
            use_double = -(is_not_first_bit_set & !use_g);
            use_double_and_sum_g = -(is_not_first_bit_set & use_g);
            is_not_first_bit_set = is_not_first_bit_set | use_g;
            use_g = ~(use_double | use_double_and_sum_g);

            double_point(result_point, &tmp_point);
            point_addition(&tmp_point, &g, result_point);

            result_point->x.limbs[0] = (SECP256K1_G_X_0 & use_g) | (tmp_point.x.limbs[0] & use_double) | (result_point->x.limbs[0] & use_double_and_sum_g);
            result_point->x.limbs[1] = (SECP256K1_G_X_1 & use_g) | (tmp_point.x.limbs[1] & use_double) | (result_point->x.limbs[1] & use_double_and_sum_g);
            result_point->x.limbs[2] = (SECP256K1_G_X_2 & use_g) | (tmp_point.x.limbs[2] & use_double) | (result_point->x.limbs[2] & use_double_and_sum_g);
            result_point->x.limbs[3] = (SECP256K1_G_X_3 & use_g) | (tmp_point.x.limbs[3] & use_double) | (result_point->x.limbs[3] & use_double_and_sum_g);

            result_point->y.limbs[0] = (SECP256K1_G_Y_0 & use_g) | (tmp_point.y.limbs[0] & use_double) | (result_point->y.limbs[0] & use_double_and_sum_g);
            result_point->y.limbs[1] = (SECP256K1_G_Y_1 & use_g) | (tmp_point.y.limbs[1] & use_double) | (result_point->y.limbs[1] & use_double_and_sum_g);
            result_point->y.limbs[2] = (SECP256K1_G_Y_2 & use_g) | (tmp_point.y.limbs[2] & use_double) | (result_point->y.limbs[2] & use_double_and_sum_g);
            result_point->y.limbs[3] = (SECP256K1_G_Y_3 & use_g) | (tmp_point.y.limbs[3] & use_double) | (result_point->y.limbs[3] & use_double_and_sum_g);
        }
    }
}
