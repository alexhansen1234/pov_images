# pov_images

Persistence of Vision (POV) Images with an APA102 on an ATMEGA328P

build binary with command:

	make

generate image headers from root directory by

	./utility/make
	./utility/image_header_gen /path/to/FILENAME.bmp >> ./src/image_headers/FILENAME_image.s

APA102 use SPI to drive data into registers.

The port and bit defintions are in assigned in

	./src/apa102/display_pixel_apa102.s

On lines

	port = 0xZZ
	clk_bit = X
	data_bit = Y

The memory map for ATMEGA328P may be found in

	./src/_avr/atmega328pmm.s

Where the alias for each IO or memory mapped register is defined

Image Transformation utilities located in directory utility.
Build Image Processor by

	./utility/make
	./utility/image_header_gen /path/to/image.bmmp

Places image header in

	./src/image_headers
