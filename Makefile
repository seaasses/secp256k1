CC = gcc
CFLAGS = -Iinclude -Wall -Wextra
SRC = src/modular_operations/modular_inverse.c src/modular_operations/modular_multiplication.c src/secp256k1/jacobian_double_point.c src/secp256k1/jacobian_to_affine.c src/secp256k1/jacobian_montgomery_to_affine.c src/montgomery/montgomery_inverse.c src/secp256k1/jacobian_point_affine_point_addition.c src/secp256k1/jacobian_point_addition_jacobian_montgomery_plus_affine_montgomery.c src/secp256k1/jacobian_montgomery_double_point.c src/montgomery/from_montgomery.c src/montgomery/to_montgomery.c src/montgomery/montgomery_reduction.c src/montgomery/montgomery_multiplication.c src/big_uint/get_random_uint256.c src/big_uint/big_uint_multiplication_helper.c src/big_uint/uint256_uint64_multiplication.c src/big_uint/uint512_addition_with_overflow_flag.c src/modular_operations/modular_double.c src/big_uint/uint256_multiplication.c src/secp256k1/g_times_scalar.c src/modular_operations/modular_subtraction.c src/modular_operations/modular_addition.c src/modular_operations/modular_double.c src/big_uint/uint64_addition_with_overflow_flag.c src/big_uint/uint64_multiplication.c src/big_uint/uint256_subtraction.c src/big_uint/uint256_subtraction_with_underflow_flag.c src/big_uint/uint320_uint256_addition.c src/big_uint/uint256_addition.c src/big_uint/uint256_addition_with_overflow_flag.c src/big_uint/uint256_shift_left.c src/big_uint/uint256_shift_right.c src/big_uint/big_uint_print.c src/unity/unity.c src/unity/unity_extension.c
TARGET = a.out 

all: $(TARGET)

$(TARGET): main.c $(SRC)
	$(CC) -O3 $(CFLAGS) $^ -o $@

compile-test: $(TARGET)
$(TARGET): main.c $(SRC)
	$(CC) -O3 -g $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)

