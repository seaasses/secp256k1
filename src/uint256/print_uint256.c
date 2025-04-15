#include <stdio.h>
#include "uint256/print_uint256.h"

void print_uint256(Uint256 x) {
    for (int i = 0; i < 4; ++i) {
        unsigned long long value = x.limbs[i];
        for (int i = 7; i >= 0; i--) {
            unsigned char byte = (value >> (i * 8));
            printf("0x%02X ", byte);
        }
    }
    printf("\n");
}