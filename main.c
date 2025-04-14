#include "include/structs/uint256.h"
#include "include/uint256/shiftLeft.h"

#include <stdio.h>
#include <stdint.h>

void printUint256(UInt256 x) {
    for (int i = 0; i < 4; ++i) {
        unsigned long long value = x.limbs[i];
        for (int i = 7; i >= 0; i--) {
            uint8_t byte = (value >> (i * 8));
            printf("0x%02X ", byte);
        }
    }
}

int main() {
    UInt256 a = (UInt256) {
        .limbs = {
            0,0,0,1
        }
    };

    UInt256 result;

    uint256ShiftLeft(&a, &result);
    printUint256(result);

}