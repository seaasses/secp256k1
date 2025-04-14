#include "structs/uint256.h"
#include "uint256/shiftLeft.h"
#include "uint256/printUint256.h"

#include <stdio.h>
#include <stdint.h>


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