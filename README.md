# SECP256K1 Implementation Project

This repository contains a C implementation of the SECP256K1 elliptic curve operations. It serves as a development and testing ground before porting the code to OpenCL for the [Address Artisan](https://github.com/seaasses/address-artisan) project.

## Purpose

The main goal is to build and test elliptic curve operations in a more manageable environment (C) before moving to OpenCL. Testing and development in OpenCL directly would be counterproductive due to its more complex debugging and testing environment.

## Testing Framework

Tests use [Unity](https://github.com/ThrowTheSwitch/Unity) for C unit testing, with the main function serving as the test runner.

### Building and Running Tests

```bash
make && ./a.out
```

## Implementation Details

### Uint256 Structure
- Uses 4 limbs of 64 bits each
- Limb 0 is the most significant

### Point Structure
- Implemented as a C struct
- Contains two Uint256 fields:
  - x coordinate
  - y coordinate
- Used for representing points on the SECP256k1 curve

### Basic Operations
1. **Uint256 Arithmetic**
   - Addition
   - Addition with overflow flag
   - Shift Left/Right operations
   - Subtraction
   - Subtraction with underflow flag

2. **Modular Operations** (mod P, where P is secp256k1's prime)
   - Modular addition
   - Modular double (optimized using shift left)
   - Modular subtraction
   - Modular multiplication (using double-and-add)
   - Modular exponentiation (using square-and-multiply)
   - Modular inversion (using Fermat's Little Theorem) 
   - Basic modulus operation

### SECP256k1 Point Operations
- Point doubling
- Point addition (A + B, where A ≠ B, A ≠ -B, neither point is infinity)
- Scalar multiplication (k * G, where G is the generator point)

## Future Optimizations

### Performance Improvements
1. **Scalar Multiplication Optimization**
   - Implementation of Jacobian coordinates
   - Reduced modular inversions
   - Sliding window technique for generator point
   - Pre-computation of points (1G through 15G using 4-bit window)

2. **Modular Arithmetic Optimization**
   - Montgomery representation for more efficient modular multiplication operations
   - Implementation will require:
     - uint512 for intermediate calculations in Montgomery arithmetic
     - Efficient 256-bit × 256-bit multiplication
     - Additional 512-bit arithmetic support

### Implementation Notes
- Focus is on optimizing the underlying multiplication operations to make Fermat's method faster
- Multiplication implementation strategy when needed:
  1. Standard 256-bit × 256-bit multiplication implementation
  2. Future optimization using Karatsuba algorithm for potential performance gains



