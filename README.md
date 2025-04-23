# SECP256K1 Implementation Project

This repository contains a C implementation of the SECP256K1 elliptic curve operations. It serves as a development and testing ground before porting the code to OpenCL for the [Address Artisan](https://github.com/seaasses/address-artisan) project. The implementation is strictly branchless - using constant-time arithmetic without conditional statements to prevent warp divergence in GPU execution.

## Purpose

The main goal is to build and test elliptic curve operations in a more manageable environment (C) before moving to OpenCL. Testing and development in OpenCL directly would be counterproductive due to its more complex debugging and testing environment. 

## Testing Framework

Tests use [Unity](https://github.com/ThrowTheSwitch/Unity) for C unit testing, with the main function serving as the test runner.

### Building and Running Tests

```bash
make && ./a.out
```

## Implementation Details

### Integer Structures
- **Uint256**
  - Uses 4 limbs of 64 bits each
  - Limb 0 is the most significant
- **Uint512**
  - Uses 8 limbs of 64 bits each
  - Used for intermediate calculations in Montgomery arithmetic
  - Essential for efficient modular multiplication operations

### Number Representation and Interfaces
- All internal operations use Montgomery form for efficient arithmetic
- The G*k operation:
  - External interface: accepts standard integer representation and returns affine coordinates
  - Internal implementation: uses Montgomery form and Jacobian coordinates
  - Montgomery to standard conversion happens only at the final result
- All other internal operations remain in Montgomery form for efficiency

### Point Structures
- Two distinct structures implemented:
  1. **Point (Affine)**
     - Contains two Uint256 fields (x, y)
     - Used for pre-computed points in sliding window
     - Stored in Montgomery form
  2. **JacobianPoint**
     - Contains three Uint256 fields (x, y, z)
     - Used for intermediate calculations

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
- Point addition using Jacobian coordinates 
- Scalar multiplication with optimized Jacobian arithmetic
- Conversion between affine and Jacobian coordinates

### Notable Optimizations
- Scalar multiplication (k*G) optimizations:
  - 8-bit sliding window implementation
  - Pre-computed points stored in affine coordinates (Montgomery form)
  - Mixed addition (affine + jacobian) for better performance
- Modular inversion using Fermat's Little Theorem with an optimized [addition chain](https://github.com/bitcoin-core/secp256k1/commit/07810d9abb8377e8f0056032bca51f8ca54ed18f) developed by Peter Dettman and Tim Ruffing
- Montgomery arithmetic throughout the internal operations
- Jacobian coordinates for intermediate point operations

## Future Optimizations

### Performance Improvements
1. **Modular Arithmetic Optimization**
   - Karatsuba algorithm implementation for large number multiplication