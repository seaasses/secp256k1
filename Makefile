CC = gcc
CFLAGS = -Iinclude -Wall -Wextra
SRC = src/modular_operations/modular_subtraction.c src/modular_operations/modular_addition.c src/modular_operations/modular_double.c src/uint256/subtraction.c src/uint256/subtraction_with_underflow_flag.c src/uint256/addition.c src/uint256/addition_with_overflow_flag.c src/uint256/shift_left.c src/uint256/shift_right.c src/uint256/print_uint256.c src/unity/unity.c src/unity/unity_extension.c
TARGET = a.out 

all: $(TARGET)

$(TARGET): main.c $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)
