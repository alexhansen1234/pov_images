BINARY := pov_display.hex
ELF := pov_display.elf

CC := avr-gcc
CC_FLAGS := -Wall -c -mmcu=atmega328p

LD := avr-ld
LD_FLAGS := -e init

OBJCOPY := avr-objcopy
OBJCOPY_FLAGS := -O ihex

SRC_DIR := src

ASM_OBJ := $(patsubst %.s, %.o, $(wildcard ./$(SRC_DIR)/*/*.s))
C_OBJ := $(patsubst %.c, %.o, $(wildcard ./$(SRC_DIR)/*.c))

ASM_SRC := $(wildcard ./$(SRC_DIR)/*.s)
C_SRC := $(wildcard ./$(SRC_DIR)/*.c)

$(BINARY): $(ELF)
	@echo Generating Binary $(BINARY)
	@$(OBJCOPY) $(OBJCOPY_FLAGS) $(ELF) $(BINARY)

$(ELF): $(ASM_OBJ) $(C_OBJ)
	@echo Linking Objects to target $(ELF)
	@$(LD) -T config/avr2.xn $(LD_FLAGS) -o $(ELF) $(ASM_OBJ) $(C_OBJ)

.s.o:
	@echo Assembling $<
	@$(CC) $(CC_FLAGS) $(ASM_INCLUDE) -o $@ $<

.c.o:
	@echo Compiling $<
	@$(CC) $(CC_FLAGS) -o $@ $<

ifdef (totally_false)
bmp_demp.hex: bmp_demo.elf
	avr-objcopy -O ihex bmp_demo.elf bmp_demo.hex
bmp_demo.elf: reset.o display_bmp.o lpm_u32.o lpm_u16.o lpm_u8.o test_image.o display_pixel_apa102.o
	avr-ld -T avr2.xn -e init -o bmp_demo.elf reset.o display_bmp.o lpm_u32.o lpm_u16.o lpm_u8.o program_address.o display_pixel_apa102.o test_image.o
reset.o: reset.s
	avr-gcc -Wall -pedantic-errors -c -mmcu=atmega328p -o reset.o reset.s
display_bmp.o: display_bmp.c progmem/progmem.h program_address.o
	avr-gcc -Wall -std=c99 -pedantic-errors -O3 -c -mmcu=atmega328p -o display_bmp.o display_bmp.c
lpm_u32.o: ./progmem/lpm_u32.s
	avr-gcc -Wall -c -mmcu=atmega328p -o lpm_u32.o ./progmem/lpm_u32.s
lpm_u16.o: ./progmem/lpm_u16.s
	avr-gcc -Wall -c -mmcu=atmega328p -o lpm_u16.o ./progmem/lpm_u16.s
lpm_u8.o: ./progmem/lpm_u8.s
	avr-gcc -Wall -c -mmcu=atmega328p -o lpm_u8.o ./progmem/lpm_u8.s
program_address.o: ./progmem/program_address.s
	avr-gcc -Wall -c -mmcu=atmega328p -o program_address.o ./progmem/program_address.s
display_pixel_apa102.o: ./apa102/display_pixel_apa102.s
	avr-gcc -Wall -c -mmcu=atmega328p -o display_pixel_apa102.o ./apa102/display_pixel_apa102.s
mario_image.o: ./mario_image.s
	avr-gcc -Wall -c -mmcu=atmega328p -o mario_image.o ./mario_image.s
test_image.o: ./test_image.s
	avr-gcc -Wall -c -mmcu=atmega328p -o test_image.o ./test_image.s
endif

clean:
	rm -f $(BINARY) $(ELF) $(ASM_OBJ) $(C_OBJ)

push:
	make clean
	git add .
	git commit -m "update"
	git push origin master
