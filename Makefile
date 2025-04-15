CC = gcc
CFLAGS = -Iinclude -Wall -Wextra
SRC = src/uint256/shift_left.c src/uint256/shift_right.c src/uint256/print_uint256.c src/unity/unity.c src/unity/unity_extension.c
TARGET = a.out 

all: $(TARGET)

$(TARGET): main.c $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)
