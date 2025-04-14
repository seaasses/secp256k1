CC = gcc
CFLAGS = -Iinclude -Wall -Wextra
SRC = src/uint256/shiftLeft.c
TARGET = a.out 

all: $(TARGET)

$(TARGET): main.c $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)
