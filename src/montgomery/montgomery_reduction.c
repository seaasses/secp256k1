#include "montgomery/montgomery_reduction.h"

#include "constants/montgomery.h"
#include "uint256/multiplication.h"
#include "uint256/subtraction.h"
#include "uint512/addition_with_overflow_flag.h"

inline void montgomery_reduction(Uint512 *t, Uint256 *result)
{
    // inplace safe
    // basically apply x * MONTGOMERY_R^(-1) mod MONTGOMERY_N

    Uint256 tmp_0 = MONTGOMERY_N_PRIME;
    Uint512 tmp_1;
    Uint512 m_times_n;
    unsigned int overflow_flag;
    unsigned long long should_subtract_n;

    uint256_multiplication((Uint256 *)(t->limbs + 4), &tmp_0, &tmp_1);

    tmp_0 = (Uint256)MONTGOMERY_N;

    uint256_multiplication((Uint256 *)(tmp_1.limbs + 4), &tmp_0, &m_times_n);

    uint512_addition_with_overflow_flag(t, &m_times_n, &tmp_1, &overflow_flag);

    // not overflow and > than n is pratically impossible in random numbers
    // need to add a better test to this
    should_subtract_n = 0;
    should_subtract_n |= (t->limbs[4] > MONTGOMERY_N_0);
    should_subtract_n |= ((t->limbs[4] == MONTGOMERY_N_0) & (t->limbs[5] > MONTGOMERY_N_1));
    should_subtract_n |= ((t->limbs[4] == MONTGOMERY_N_0) & (t->limbs[5] == MONTGOMERY_N_1) & (t->limbs[6] > MONTGOMERY_N_2));
    should_subtract_n |= ((t->limbs[4] == MONTGOMERY_N_0) & (t->limbs[5] == MONTGOMERY_N_1) & (t->limbs[6] == MONTGOMERY_N_2) & (t->limbs[7] >= MONTGOMERY_N_3));

    should_subtract_n = -(should_subtract_n | ((unsigned long long)overflow_flag));

    tmp_0 = (Uint256){
        .limbs = {
            MONTGOMERY_N_0 & should_subtract_n,
            MONTGOMERY_N_1 & should_subtract_n,
            MONTGOMERY_N_2 & should_subtract_n,
            MONTGOMERY_N_3 & should_subtract_n,
        }};

    uint256_subtraction((Uint256 *)(&tmp_1), &tmp_0, result);
}