# Directories
SRC_DIR = src
OBJ_DIR = build
BIN_DIR = bin

# Compiler
CC = gcc
CFLAGS = -Wall -Wextra

# Source and Object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Main target
TARGET = $(BIN_DIR)/main

# Create directories
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))


# Build
$(TARGET): $(OBJ_FILES)
	$(CC) $^ -o $@

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)