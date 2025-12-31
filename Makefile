CC = gcc 
CFLAGS = -std=c11 -O3 -Wall -Wextra -Wpedantic -D_POSIX_C_SOURCE=200809L

TARGET = hexview
SRC_DIR = src
BUILD_DIR = build

# Mapeia src/main.c para build/main.o
SRCS = $(SRC_DIR)/main.c
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(TARGET)

# Cria o executável na raiz
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Cria .o em build/ e garante que a pasta exista
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean