#include "structs/uint256.h"
#include "uint256/shift_left.h"
#include "uint256/print_uint256.h"

#include <stdio.h>
#include <stdint.h>


int main() {
    UInt256 a = (UInt256) {
        .limbs = {
            0,0,0,1
        }
    };

    UInt256 result;

    uint256_shift_left(&a, &result);
    print_uint256(result);

}