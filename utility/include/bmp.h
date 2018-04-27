#include <stdio.h>
#include <stdlib.h>

#ifndef _BMP_H_
  #define _BMP_H_ 1

struct BMP
{
    char      identifier[2];
    uint32_t  file_size;
    uint16_t  reserved1;
    uint16_t  reserved2;
    uint32_t  pixel_array_offset;
    uint32_t  DIB_header_size;
    uint32_t  width;
    uint32_t  height;
    uint16_t  planes;
    uint16_t  bits_per_pixel;
    uint32_t  compression;
    uint32_t  image_size;
    uint32_t  x_pix_per_meter;
    uint32_t  y_pix_per_meter;
    uint32_t  colors_in_table;
    uint32_t  important_color_count;
    uint32_t  red_channel_bitmask;
    uint32_t  green_channel_bitmask;
    uint32_t  blue_channel_bitmask;
    uint32_t  color_space_type;
    uint32_t  color_space_endpoints;
    uint32_t  gamma_red_channel;
    uint32_t  gamma_green_channel;
    uint32_t  gamma_blue_channel;
    uint32_t  intent;
    uint32_t  icc_profile_data_location;
    uint32_t  icc_profile_size;
    uint32_t  reserved3;
    uint32_t  *color_table;
    uint8_t   *data;
    uint8_t   *icc_color_profile_data;
};

struct BMP * getBMP(FILE *);
void free_BMP(struct BMP *);
void print_BMP(struct BMP *);
void generate_image_header_atmega328p(struct BMP *, const char *, const char *);
#endif
