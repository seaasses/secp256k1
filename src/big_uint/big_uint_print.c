#include <stdio.h>
#include "big_uint/big_uint_print.h"

void big_uint_print(unsigned long long *limbs, unsigned int quant)
{
    for (unsigned int i = 0; i < quant; ++i)
    {
        printf("%d: 0x%016llX\n", i, limbs[i]);
    }
    printf("\n");
}

void uint256_print(Uint256 *x)
{
    big_uint_print((unsigned long long*)x, 4);
}

void uint512_print(Uint512 *x)
{
    big_uint_print((unsigned long long*)x, 8);
}