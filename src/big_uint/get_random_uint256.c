#include "big_uint/get_random_uint256.h"
#include <stdlib.h>

unsigned long long rand64()
{
    unsigned long long r = 0;
    for (int i = 0; i < 4; ++i)
    {
        r = (r << 16) | (rand() & 0xFFFF);
    }
    return r;
}

Uint256 get_random_uint256(void)
{
    Uint256 result;
    for (int i = 0; i < 4; ++i)
    {
        result.limbs[i] = rand64();
    }

    return result;
}