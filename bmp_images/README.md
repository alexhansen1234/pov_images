Place Bitmap Images in this Directory

Bitmaps must be compressed to Run Length Encoding 4 format

To build image headers:

    cd /path/to/pov_images/utility

    make

    image_header_gen /path/to/$(bmp_file).bmp

Header files will be placed in:

    /path/to/pov_images/src/image_headers/

With file name:

    /$(bmp_file)_image.s
