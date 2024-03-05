# Directories
SRC_DIR = src
OBJ_DIR = build
BIN_DIR = bin
INCLUDE_DIR = include

# SDL flags
SDL_CFLAGS = $(shell sdl2-config --cflags)
SDL_LFLAGS = $(shell sdl2-config --libs)

# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -std=c17 -I$(INCLUDE_DIR)

# Source and Object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Main target
TARGET = $(BIN_DIR)/main

# Create directories
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))


# Build
$(TARGET): $(OBJ_FILES)
	$(CC) $^ $(SDL_LFLAGS) -o $@

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(SDL_CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)