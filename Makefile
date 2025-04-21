CC = gcc
CFLAGS = -Iinclude -Wall -Wextra
SRC = src/montgomery/montgomery_inverse.c src/secp256k1/jacobian_point_addition_jacobian_montgomery_plus_affine_montgomery.c src/secp256k1/jacobian_montgomery_double_point.c src/montgomery/from_montgomery.c src/montgomery/to_montgomery.c src/montgomery/montgomery_reduction.c src/montgomery/montgomery_multiplication.c src/uint512/addition_with_overflow_flag.c src/modular_operations/modular_double.c src/uint256/multiplication.c src/secp256k1/jacobian_point_addition_jacobian_plus_affine.c src/secp256k1/jacobian_double_point.c src/secp256k1/g_times_scalar.c src/secp256k1/jacobian_to_affine.c src/modular_operations/modular_exponentiation.c src/modular_operations/modular_multiplication.c src/modular_operations/modular_subtraction.c src/modular_operations/modular_addition.c src/modular_operations/modular_double.c src/uint256/subtraction.c src/uint256/subtraction_with_underflow_flag.c src/uint256/addition.c src/uint256/addition_with_overflow_flag.c src/uint256/shift_left.c src/uint256/shift_right.c src/uint256/print_uint256.c src/unity/unity.c src/unity/unity_extension.c
TARGET = a.out 

all: $(TARGET)

$(TARGET): main.c $(SRC)
	$(CC) -O3 $(CFLAGS) $^ -o $@

compile-test: $(TARGET)
$(TARGET): main.c $(SRC)
	$(CC) -O3 -g $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)

