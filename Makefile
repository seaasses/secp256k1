CC = gcc
CFLAGS = -Iinclude -Wall -Wextra
SRC = src/uint256/shift_left.c src/uint256/print_uint256.c
TARGET = a.out 

all: $(TARGET)

$(TARGET): main.c $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)
