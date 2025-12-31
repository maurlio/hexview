# Compilador
CC := gcc

# Diretórios
SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include

# Arquivo final
TARGET := hexview

# Flags
CFLAGS := -std=c11 -O3 -Wall -Wextra -Wpedantic -I$(INCLUDE_DIR)
LDFLAGS :=

# Fontes e objetos
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

# Alvo padrão
all: $(TARGET)

# Linkagem
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# Compilação com geração de dependências
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Cria diretório build se não existir
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Inclui dependências automaticamente
-include $(DEPS)

# Executa o programa
run: $(TARGET)
	./$(TARGET)

# Limpeza
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean run
