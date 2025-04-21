#include "montgomery/montgomery_multiplication.h"
#include "uint256/multiplication.h"
#include "uint512/addition_with_overflow_flag.h"
#include "uint256/subtraction.h"
#include "constants/montgomery.h"
#include "structs/uint512.h"
#include <stdio.h>

inline void montgomery_multiplication(Uint256 *a_m, Uint256 *b_m, Uint256 *result_m)
{

    Uint256 tmp_0 = MONTGOMERY_N_PRIME;
    Uint512 tmp_1;

    Uint512 t;
    Uint512 m_times_n;
    unsigned int overflow_flag;

    uint256_multiplication(a_m, b_m, &t); 

    uint256_multiplication((Uint256 *)(t.limbs + 4), &tmp_0, &tmp_1);

    tmp_0 = (Uint256)MONTGOMERY_N;

    uint256_multiplication((Uint256 *)(tmp_1.limbs + 4), &tmp_0, &m_times_n);

    uint512_addition_with_overflow_flag(&t, &m_times_n, &tmp_1, &overflow_flag);

    // TODO:  the probability of only this occurring is very low (not overflowing but > MONTGOMERY_N).
    // Need to add a test for this case
    result_m->limbs[0] = 0;
    result_m->limbs[0] |= (t.limbs[4] > MONTGOMERY_N_0);
    result_m->limbs[0] |= ((t.limbs[4] == MONTGOMERY_N_0) & (t.limbs[5] > MONTGOMERY_N_1));
    result_m->limbs[0] |= ((t.limbs[4] == MONTGOMERY_N_0) & (t.limbs[5] == MONTGOMERY_N_1) & (t.limbs[6] > MONTGOMERY_N_2));
    result_m->limbs[0] |= ((t.limbs[4] == MONTGOMERY_N_0) & (t.limbs[5] == MONTGOMERY_N_1) & (t.limbs[6] == MONTGOMERY_N_2) & (t.limbs[7] >= MONTGOMERY_N_3));

    result_m->limbs[0] = -(result_m->limbs[0] | ((unsigned long long)overflow_flag));

    tmp_0 = (Uint256){
        .limbs = {
            MONTGOMERY_N_0 & result_m->limbs[0],
            MONTGOMERY_N_1 & result_m->limbs[0],
            MONTGOMERY_N_2 & result_m->limbs[0],
            MONTGOMERY_N_3 & result_m->limbs[0],
        }};

    uint256_subtraction((Uint256 *)(&tmp_1), &tmp_0, result_m);
}