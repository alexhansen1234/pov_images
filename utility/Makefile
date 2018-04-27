# Target Binary
TARGET := image_header_gen

# Compiler
CC := gcc
C_FLAGS := -O3
CPP_FLAGS :=

# Directories
SRC_DIR := src
INCLUDE_DIR := include
OBJ_DIR := obj

# Libraries
LIBS :=

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

$(TARGET): $(OBJ_DIR) $(OBJ)
	@echo Building binary $@
	@$(CC) $(C_FLAGS) $(OBJ) $(LIBS) -o $@

$(OBJ_DIR):
	@echo Creating directory $@
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo Compiling $< to $@
	@$(CC) $(C_FLAGS) $(CPP_FLAGS) -c -o $@ $<

clean:
	@echo Removing $(OBJ)
	@rm -f -r obj

cleaner:
	@echo Removing $(TARGET)
	@make clean
	@rm $(TARGET)
