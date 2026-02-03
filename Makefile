# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -Iinclude
# The -Iinclude flag tells gcc to look in the 'include' folder!

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN = game

# Source and Object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Default Target
all: $(BIN)

# Link
$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lm

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(OBJ_DIR) $(BIN)

.PHONY: all clean
