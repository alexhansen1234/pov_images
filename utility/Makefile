# Target Binary
TARGET := image_header_gen

# Compiler
CC := gcc
C_FLAGS := -O3
CPP_FLAGS :=

SRC_DIR := src
INCLUDE_DIR := include
BIN_DIR := bin
DIR := $(lastword $(subst /, , $(shell pwd)))

# Libraries
LIBS :=

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRC))

$(TARGET): $(BIN_DIR) $(OBJ)
	@echo Building binary $@
	@$(CC) $(C_FLAGS) $(OBJ) $(LIBS) -o $@

$(BIN_DIR):
	@echo Creating directory $@
	@mkdir $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@echo Compiling $< to $@
	@$(CC) $(C_FLAGS) $(CPP_FLAGS) -c -o $@ $<

clean:
	@if [ -d $(BIN_DIR) ]; then\
		echo Removing $(patsubst %, $(DIR)/%, $(OBJ));\
		echo Removing Directory $(patsubst %, $(DIR)/%, $(BIN_DIR));\
		rm -f -r $(BIN_DIR);\
	fi

cleaner:
	@make clean
	@if [ -e $(TARGET) ]; then\
		echo Removing $(DIR)/$(TARGET);\
		rm $(TARGET);\
	fi
