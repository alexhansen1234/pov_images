#include <stdlib.h>
#include <stdio.h>
#include "../include/bmp.h"

int main(int argc, char ** argv)
{
  FILE *fp;
  struct BMP * bmp;

  if(argc == 1)
  {
    printf("Missing Path to File\n");
    return 1;
  }

  fp = fopen(argv[1], "r");
  bmp = getBMP(fp);
  print_BMP(bmp);
  generate_image_header_atmega328p(bmp, argv[1]);
  free_BMP(bmp);
}
