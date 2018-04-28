# pov_images

Persistence of Vision (POV) Images with an APA102 on an ATMEGA328P

build binary with command:

	make

generate image headers from root directory by

	./utility/make
	./utility/image_header_gen /path/to/FILENAME.bmp >> ./src/image_headers/FILENAME_image.s

APA102 use SPI to drive data into shift registers, which require clock and data lines.

Output port, clk_bit and data_bit need to be defined in

	./src/apa102/display_pixel_apa102.s

On lines

	port = 0xZZ
	clk_bit = X
	data_bit = Y

Currently, clk_bit and data_bit are bit fields in register port, but the source can easily
be modified to have separate registers control clock and data lines.

The memory map for ATMEGA328P may be found in

	./src/_avr/atmega328pmm.s

Where the alias for each IO or memory mapped register is defined

Image Transformation utilities located in directory utility.
Build Image Processor by

	./utility/make
	./utility/image_header_gen /path/to/image.bmmp

Places image header in

	./src/image_headers
