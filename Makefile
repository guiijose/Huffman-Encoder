CC = gcc
CFLAGS_DEV = -Wall -Wextra -Werror -pedantic -g -std=c11
CFLAGS_PROD = -O2 -Wall -std=c11
INCLUDES = -Iinclude
SRC = src/main.c src/file_utils.c src/huffman.c
OBJ = $(SRC:.c=.o)
TARGET = bin/huffman

.PHONY: all dev prod clean

all: dev

dev: CFLAGS = $(CFLAGS_DEV)
dev: $(TARGET)

prod: CFLAGS = $(CFLAGS_PROD)
prod: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf src/*.o bin
