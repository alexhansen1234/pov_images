/*
 *  Source for manipulating BMP images and generating assembly tables with
 *  Run Length Encoding (4bit) formatted BMP data.
 *
 *  Maybe will one-day support RLE8, for larger color tables.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/bmp.h"

struct BMP * getBMP(FILE *fp)
{
  struct BMP *bmp = (struct BMP *)calloc(sizeof(struct BMP), 1);

  fread((void *)&bmp->identifier, 2, 1, fp);
  fread((void *)&bmp->file_size, 4, 1, fp);
  fread((void *)&bmp->reserved1, 2, 1, fp);
  fread((void *)&bmp->reserved2, 2, 1, fp);
  fread((void *)&bmp->pixel_array_offset, 4, 1, fp);
  fread((void *)&bmp->DIB_header_size, 4, 1, fp);
  fread((void *)&bmp->width, bmp->DIB_header_size - 4, 1, fp);

  if(bmp->compression)
  {
    bmp->color_table = (uint32_t *)calloc(sizeof(uint8_t)*(bmp->pixel_array_offset - 54), 1);
    fread((void *)bmp->color_table, sizeof(uint8_t) * (bmp->pixel_array_offset - 54), 1, fp);
  }
  else
  {
    bmp->color_table = 0;
  }

  rewind(fp);
  fseek(fp, bmp->pixel_array_offset, 0);

  bmp->data = (uint8_t *)malloc(sizeof(uint8_t) * bmp->image_size);

  fread((void *)bmp->data, sizeof(uint8_t) * bmp->image_size, 1, fp);

  if(bmp->icc_profile_size)
  {
    bmp->icc_color_profile_data = (uint8_t *)malloc(sizeof(uint8_t) * bmp->icc_profile_size);

    fread((void *)bmp->icc_color_profile_data, sizeof(uint8_t) * bmp->icc_profile_size, 1, fp);
  }
  else
  {
    bmp->icc_color_profile_data = 0;
  }

  return bmp;
}

void print_BMP(struct BMP * bmp)
{
  printf("ID: %c%c\nFile Size: %u\nReserved1: %u\nReserved2: %u\nPixel Array Offset: %u\n", *bmp->identifier, *(bmp->identifier+1), bmp->file_size, bmp->reserved1, bmp->reserved2, bmp->pixel_array_offset);
  printf("DIB Header Size: %u\n", bmp->DIB_header_size);
  printf("Width: %u\n", bmp->width);
  printf("Height: %u\n", bmp->height);
  printf("Planes: %u\n", bmp->planes);
  printf("Bits Per Pixel: %u\n", bmp->bits_per_pixel);
  printf("Compression: %u\n", bmp->compression);
  printf("Image Size: %u\n", bmp->image_size);
  printf("X Pixels per Meter: %u\n", bmp->x_pix_per_meter);
  printf("Y Pixels per Meter: %u\n", bmp->y_pix_per_meter);
  printf("Colors in Table: %u\n", bmp->colors_in_table);
  printf("Important Color Count: %u\n", bmp->important_color_count);
  printf("Red Channel Bitmask: %u\n", bmp->red_channel_bitmask);
  printf("Green Channel Bitmask: %u\n", bmp->green_channel_bitmask);
  printf("Blue Channel Bitmask: %u\n", bmp->blue_channel_bitmask);
  printf("Color Space Type: %u\n", bmp->color_space_type);
  printf("Color Space Endpoints: %u\n", bmp->color_space_endpoints);
  printf("Gamma Red Channel: %u\n", bmp->gamma_red_channel);
  printf("Gamma Green Channel: %u\n", bmp->gamma_green_channel);
  printf("Gamma Blue Channel: %u\n", bmp->gamma_blue_channel);
  printf("Intent: %u\n", bmp->intent);
  printf("ICC Profile Data Location: %u\n", bmp->icc_profile_data_location);
  printf("ICC Profile Size: %u\n", bmp->icc_profile_size);
  int i=0;
  int j=0;
  if(bmp->compression)
  {
    while(i < ((bmp->pixel_array_offset - 54)>>2))
    {
      if(i==0) printf("Color Table Entries:\n");
      printf("%d.\t%03u\n", i, *((bmp->color_table + i)));
      i++;
    }
  }

  i=0;
  switch(bmp->compression)
  {
    case 0: // Uncompressed
            while(i < bmp->image_size)
            {
              if(i==0) printf("Data Array:\n");
              if(!(i % (bmp->width * (bmp->bits_per_pixel >> 3)))) printf("\n");
              printf("%03u ", *(bmp->data + i));
              i++;
            }
            break;
    case 1: // 8-bit RLE
            while(i < bmp->image_size)
            {
              if(i==0) printf("Data Array:\n");

              if(*(bmp->data + i))
              {
                printf("%03u %03u ", *(bmp->data + i), *(bmp->data + i + 1));
                i += 2;
              }
              else
              {
                switch(*(bmp->data + i + 1))
                {
                  case 0: // End of Line
                  case 1: // End of File
                  case 2: // Delta
                          printf("%03u %03u\n", *(bmp->data + i), *(bmp->data + i + 1));
                          i += 2;
                          break;
                  default:
                          j = 0;
                          printf("%03u ", *(bmp->data + i));
                          while(j <= *(bmp->data + i + 1))
                          {
                            printf("%03u ", *(bmp->data + i + j + 1));
                            j++;
                          }
                          if((j-1) % 2)
                          {
                            while((j-1) % 2)
                            {
                              printf("%03u ", *(bmp->data + i + j + 1));
                              j++;
                            }
                          }
                          i += j+1;
                }
              }
            }
            break;
    case 2: // 4-bit RLE
            while(i < bmp->image_size)
            {
              if(i==0) printf("Data Array:\n");

              if(*(bmp->data + i))
              {
                printf("%02x %02x ", *(bmp->data + i), *(bmp->data + i + 1));
                i += 2;
              }
              else
              {
                switch(*(bmp->data + i + 1))
                {
                  case 0: // End of Line
                  case 1: // End of File
                  case 2: // Delta
                          printf("%02x %02x\n", *(bmp->data + i), *(bmp->data + i + 1));
                          i += 2;
                          break;
                  default:
                          j = 0;
                          printf("%02x ", *(bmp->data + i));
                          while(j <= (*(bmp->data + i + 1)/2))
                          {
                            printf("%02x ", *(bmp->data + i + j + 1));
                            j++;
                          }
                          if((j-1) % 2)
                          {
                            while((j-1) % 2)
                            {
                              printf("%02x ", *(bmp->data + i + j + 1));
                              j++;
                            }
                          }
                          i += j+1;
                }
              }
            }
            break;
  }
  printf("\n");
}

void free_BMP(struct BMP * bmp)
{
  if(bmp->color_table)
    free(bmp->color_table);
  if(bmp->icc_color_profile_data)
    free(bmp->icc_color_profile_data);
  free(bmp->data);
  free(bmp);
}

void generate_image_header_atmega328p(struct BMP * bmp, const char * original_file_name)
{
  int size = 0;
  int i=0, j=0;
  int exit_loop = 0;
  int padding_byte = 0;
  char * file_name = (char *)malloc(sizeof(char));

  while(*(original_file_name + i))
  {
    if(*(original_file_name + i) == '/')
      j = i+1;
    i++;
  }

  i = 0;

  while(*(original_file_name + j) != '.')
  {
    size++;
    file_name = (char *)realloc(file_name, sizeof(char) * (size + 1));
    *(file_name + size - 1) = *(original_file_name + j);
    j++;
  }
  *(file_name + j) = '\0';

  size = 0;
  char * string = file_name;
  char * output_file_name = (char *)malloc(sizeof(char) * (strlen("_image.s") + strlen(string) + 1));
  strcpy(output_file_name, string);
  strcat(output_file_name, "_image.s");

  FILE * fp = fopen(output_file_name, "w");

  switch(bmp->compression)
  {
    case 0:
            printf("Uncompressed BMP file.\n");
            printf("No Method for Generating Header.\n");
            printf("Exiting.\n");
            break;
    case 1:
            printf("Compression: 8-bit RLE BMP\n");
            printf("No Method for Generating Header.\n");
            printf("Exiting.");
            break;
    case 2:
            // Run through once to get final size of array object
            while(i < bmp->image_size && !exit_loop)
            {
                if(*(bmp->data + i))
                {
                  i += 2;
                  size += 2;
                }
                else
                {
                  switch(*(bmp->data + i + 1))
                  {
                    case 0:
                            i += 2;
                            size += 2;
                            break;
                    case 1:
                            size += 2;
                            exit_loop = 1;
                            break;
                    case 2:
                            i += 2;
                            size += 2;
                            break;
                    default:
                            j = 0;
                            while(j <= (*(bmp->data + i + 1))>>1)
                            {
                              j++;
                            }
                            i += j + 1 + (*(bmp->data + i + 1) % 4)/2;
                            size += j + 1;
                  }
                }
            }

            if(size % 2)
            {
              size += 1;
              padding_byte = 1;
            }
            printf("Generating ATMEGA328P Image Header...\n");
            printf("Input File: %s\n", original_file_name);
            printf("Output File: %s\n", output_file_name);
            printf("Compression: 4-bit RLE BMP\n");
            printf("Padding Bytes Removed\n");

            /* PRINT FILE NAME */
            fprintf(fp, ".file \"%s_image.s\"\n", string);
            fprintf(fp, "\n");

            /* PRINT SIZE */
            fprintf(fp, ".global %s_data_size\n", string);
            fprintf(fp, "\t.text\n");
            fprintf(fp, "\t.type %s_data_size, @object\n", string);
            fprintf(fp, "\t.size %s_data_size, 2\n", string);
            fprintf(fp, "%s_data_size:\n", string);
            fprintf(fp, "\t.word %s_data_end - %s_data\n", string, string);
            fprintf(fp, "\n");

            /* PRINT COLOR TABLE SIZE */
            fprintf(fp, ".global %s_color_table_size\n", string);
            fprintf(fp, "\t.text\n");
            fprintf(fp, "\t.type %s_color_table_size, @object\n", string);
            fprintf(fp, "\t.size %s_color_table_size, 2\n", string);
            fprintf(fp, "%s_color_table_size:\n", string);
            fprintf(fp, "\t.word %s_color_table_end - %s_color_table\n", string, string);
            fprintf(fp, "\n");


            /* PRINT COLOR TABLE */
            fprintf(fp, ".global %s_color_table\n", string);
            fprintf(fp, "\t.text\n");
            fprintf(fp, "\t.type %s_color_table, @object\n", string);
            fprintf(fp, "\t.size %s_color_table, %d\n", string, bmp->colors_in_table * 4);
            fprintf(fp, "%s_color_table:\n", string);

            i=0;

            while(i < bmp->colors_in_table)
            {
              fprintf(fp, "\t.word 0x%04x\n\t.word 0x%04x\n", *(bmp->color_table+i)&0xFFFF, *(bmp->color_table+i) >> 16);
              i++;
            }
            fprintf(fp, "%s_color_table_end:\n", string);
            fprintf(fp, "\n");

            /* PRINT HEIGHT */
            fprintf(fp, ".global %s_height\n", string);
            fprintf(fp, "\t.text\n");
            fprintf(fp, "\t.type %s_height, @object\n", string);
            fprintf(fp, "\t.size %s_height, %lu\n", string, sizeof(bmp->height));
            fprintf(fp, "%s_height:\n", string);
            fprintf(fp, "\t.word 0x%04x\n", (bmp->height)&0xFFFF);
            fprintf(fp, "\t.word 0x%04x\n", (bmp->height>>16)&0xFFFF);
            fprintf(fp, "\n");

            /* PRINT WIDTH */
            fprintf(fp, ".global %s_width\n", string);
            fprintf(fp, "\t.text\n");
            fprintf(fp, "\t.type %s_width, @object\n", string);
            fprintf(fp, "\t.size %s_width, %lu\n", string, sizeof(bmp->width));
            fprintf(fp, "%s_width:\n", string);
            fprintf(fp, "\t.word 0x%04x\n", (bmp->width)&0xFFFF);
            fprintf(fp, "\t.word 0x%04x\n", (bmp->width>>16)&0xFFFF);
            fprintf(fp, "\n");

            /* PRINT INDEX DATA */
            fprintf(fp, ".global %s_data\n", string);
            fprintf(fp, "\t.text\n");
            fprintf(fp, "\t.type %s_data, @object\n", string);
            fprintf(fp, "\t.size %s_data, %d\n", string, size);
            fprintf(fp, "%s_data:\n", string);

            i = 0;
            j = 0;
            uint32_t line_counter = 0;
            exit_loop = 0;

            while(i < bmp->image_size && !exit_loop)
            {
                if(*(bmp->data + i))
                {
                  fprintf(fp, "\t.byte 0x%02x /* %x */\n\t.byte 0x%02x /* %x */\n", *(bmp->data + i), line_counter++, *(bmp->data + i + 1), line_counter++);
                  i += 2;
                }
                else
                {
                  switch(*(bmp->data + i + 1))
                  {
                    case 0:
                            fprintf(fp, "\t.byte 0x%02x /* %x */\n\t.byte 0x%02x /* %x */\n", *(bmp->data + i), line_counter++, *(bmp->data + i + 1), line_counter++);
                            i += 2;
                            break;
                    case 1:
                            fprintf(fp, "\t.byte 0x%02x /* %x */\n\t.byte 0x%02x /* %x */\n", *(bmp->data + i), line_counter++, *(bmp->data + i + 1), line_counter++);
                            if(padding_byte)
                            {
                              fprintf(fp, "\t.byte 0x00\n");
                            }
                            fprintf(fp, "%s_data_end:\n", string);
                            exit_loop = 1;
                            break;
                    case 2:
                            fprintf(fp, "\t.byte 0x%02x /* %x */\n\t.byte 0x%02x /* %x */\n", *(bmp->data + i), line_counter++, *(bmp->data + i + 1), line_counter++);
                            i += 2;
                            break;
                    default:
                            j = 0;
                            fprintf(fp, "\t.byte 0x%02x /* %x */\n", *(bmp->data + i), line_counter++);
                            while(j <= (*(bmp->data + i + 1))>>1)
                            {
                              fprintf(fp, "\t.byte 0x%02x /* %x */\n", *(bmp->data + i + j + 1), line_counter++);
                              j++;
                            }
                            i += j + 1 + (*(bmp->data + i + 1) % 4)/2;
                  }
                }
            }
            break;
      default:
                printf("Error\n");
                return;
  }
  free(file_name);
  free(output_file_name);
  fclose(fp);
}
