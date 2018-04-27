# pov_images

Persistence of Vision (POV) Images with an APA102 on an ATMEGA328P

build binary with command:

	make

generate image headers from root directory by

	./utility/make
	./utility/image_header_gen /path/to/FILENAME.bmp >> ./src/image_headers/FILENAME_image.s

Image Transformation utilities located in directory util.
Reads RLE4 Bitmap images and outputs data encoded in an ATMEGA328P assembly style array.
This is beneficial for start-up because array data will be stored in program memory (the heap)
rather than on the stack.

In future revisions, make will run a sript to look for all included images in
`src/image_headers` and build a C source file containing an array of pointers
which would allow for changing displayed images on the fly.

Image change, and program/pattern change in general will be handled by an interrupt driven
system which will alter a global variable controlling pattern behavior.
