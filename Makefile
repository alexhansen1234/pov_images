BINARY := pov_display.hex
ELF := pov_display.elf

CC := avr-gcc
CC_FLAGS := -Wall -c -mmcu=atmega328p

LD := avr-ld
LD_FLAGS := -e init
LD_CONFIG := -T ./config/avr2.xn

OBJCOPY := avr-objcopy
OBJCOPY_FLAGS := -O ihex

SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := src/bin

ASM_SRC := $(wildcard $(SRC_DIR)/*/*.s)
C_SRC := $(wildcard $(SRC_DIR)/*.c)

ASM_OBJ := $(patsubst %.s, $(BUILD_DIR)/%.o, $(notdir $(ASM_SRC)))
C_OBJ := $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(C_SRC)))

SUBDIR := $(wildcard */.)
SUBDIR_CMD := cleaner

$(BINARY): $(BUILD_DIR) $(BUILD_DIR)/$(ELF)
	@echo Generating Binary $@
	@$(OBJCOPY) $(OBJCOPY_FLAGS) $(BUILD_DIR)/$(ELF) $(BINARY)

$(BUILD_DIR):
	@echo Creating Directory $@
	@mkdir $(BUILD_DIR)

$(BUILD_DIR)/$(ELF): $(ASM_OBJ) $(C_OBJ)
	@echo Linking Objects to $@
	@$(LD) $(LD_CONFIG) $(LD_FLAGS) -o $(BUILD_DIR)/$(ELF) $(ASM_OBJ) $(C_OBJ)

$(BUILD_DIR)/%.o: $(SRC_DIR)/*/%.s
	@echo Assembling $@ from $<
	@$(CC) $(CC_FLAGS) -o $(BUILD_DIR)/$(notdir $@) $<

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo Compiling $@ from $<
	@$(CC) $(CC_FLAGS) -o $(BUILD_DIR)/$(notdir $@) $<

clean:
	@if [ -d $(BUILD_DIR) ]; then\
		echo Removing Directory $(BUILD_DIR);\
		rm -rf $(BUILD_DIR);\
	fi

cleaner: $(SUBDIR)
	@make clean
	@if [ -e $(BINARY) ]; then\
		echo Removing Binary $(BINARY);\
		rm -f $(BINARY);\
	fi

push:
	@make cleaner
	git add .
	git commit -m "update"
	git push origin master

$(SUBDIR):
	@if [ -e $@/Makefile ]; then\
		$(MAKE) -C $@ $(SUBDIR_CMD);\
	fi

.PHONY: $(SUBDIR)
