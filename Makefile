# Compiler and flags
CC = gcc
CFLAGS = -Wall -I./include

# Folders
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/directory_ops.c $(SRC_DIR)/file_ops.c $(SRC_DIR)/logger.c $(SRC_DIR)/permissions.c $(SRC_DIR)/color_utils.c
# Target object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Output file
TARGET = $(BIN_DIR)/mainProgram

# Default target: compile and run
all: $(TARGET)

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link the program
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $(TARGET)

# Run the program
run: $(TARGET)
	$(TARGET)

# Cleaning
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Cleaning object files and output
fclean: clean
	rm -f $(TARGET)

# Compilation process only
re: fclean all
