Place Bitmap Images in this Directory

Bitmaps must be compressed to Run Length Encoding 4 format

Build Image Headers by runnning

  cd /path/to/pov_images/utility

  make

  image_header_gen /path/to/$(bmp_file).bmp

The output from image_header_gen wil be located in directory

  /path/to/pov_images/src/image_headers/

With file name

  /$(bmp_file)_image.s
