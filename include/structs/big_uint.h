#ifndef BIG_UINT
#define BIG_UINT

typedef struct
{
    unsigned long long limbs[2];
} Uint128;

typedef struct
{
    unsigned long long limbs[4];
} Uint256;

typedef struct
{
    unsigned long long limbs[5];
} Uint320;

typedef struct
{
    unsigned long long limbs[8];
} Uint512;

#endif