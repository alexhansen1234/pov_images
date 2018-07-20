#include <stdint.h>
#include "../../include/progmem.h"
#include "../../include/apa102.h"

#define NUM_PIXELS 144

struct BMP_HEADER
{
  uint16_t    size;
  uint32_t    height;
  uint32_t    width;
  uint32_t *  color_table;
  uint16_t    color_table_n_elem;
  uint8_t  *  data;
};

extern uint16_t   mario_data_size;
extern uint32_t   mario_height;
extern uint32_t   mario_width;
extern uint32_t * mario_color_table;
extern uint8_t  * mario_data;

extern uint16_t   test_data_size;
extern uint16_t   test_color_table_size;
extern uint32_t   test_height;
extern uint32_t   test_width;
extern uint32_t * test_color_table;
extern uint8_t  * test_data;

void display_bmp(struct apa102 *, struct BMP_HEADER *);

int main()
{
    uint32_t pixels[NUM_PIXELS];
    //struct ws2812 strip;
    struct BMP_HEADER test;
    /*struct BMP_HEADER mario;*/

    //strip.num_pixels = NUM_PIXELS;
    //strip.pixels = pixels;

    struct apa102 strip102;

    strip102.num_pixels = NUM_PIXELS;
    strip102.pixels = pixels;
    strip102.brightness = 2;

    test.size         = lpm_u16(&test_data_size);
    test.color_table_n_elem = lpm_u16(&test_color_table_size) >> 2;
    test.height       = lpm_u32(&test_height);
    test.width        = lpm_u32(&test_width);
    test.color_table  = program_address(&test_color_table);
    test.data         = program_address(&test_data);

/*
    mario.size    = lpm_u16(&mario_data_size);
    mario.height  = lpm_u32(&mario_height);
    mario.width   = lpm_u32(&mario_width);
    mario.color_table  = program_address(&mario_color_table);
    mario.data    = program_address(&mario_data);
*/

    while(1)
    {
      display_bmp(&strip102, &test);
        /*display_bmp(&strip, &mario);*/
    }

}

void display_bmp(struct apa102 * strip, struct BMP_HEADER * bmp_header)
{
  uint32_t  color_table[bmp_header->color_table_n_elem];
  uint32_t  current_data_offset = 0;
  uint8_t   current_data;
  uint16_t  current_width = 0;
  uint16_t  current_height = 0;
  uint16_t  delta_width;
  uint16_t  delta_height;
  uint8_t   run_length;
  uint8_t   run_counter;
  uint8_t   counter;
  counter = 0;

  while(counter < bmp_header->color_table_n_elem)
  {
      color_table[counter] = lpm_u32(bmp_header->color_table + counter);
      counter++;
  }

  while(current_data_offset < bmp_header->size)
  {
    if((run_length = lpm_u8(bmp_header->data + current_data_offset)))
    {
      /* RUN-LENGTH ENCODING HANDLER */
      /* If current_data is not zero, current_data is the run-length */
      /* the byte after current_data is the pair of 4-bit values to be repeated current_data times */
      /* each nibble is displayed, and the counter increases */
      /* Ex. If current_data is 0x05 and current_data + 1 is 0x73 */
      /* the displayed colors will be 7 3 7 3 7 where 7 and 3 are indicies in the color table */
      counter = 0;
      current_data = lpm_u8(bmp_header->data + current_data_offset + 1);
      while(counter < run_length)
      {
        if(counter & 0x01)
        {
          strip->pixels[current_width] = color_table[(current_data & 0x0F)];
        }
        else
        {
          strip->pixels[current_width] = color_table[(current_data >> 4)];
        }
        current_width++;
        counter++;
      }
      current_data_offset += 2;
    }
    else
    {
      switch((current_data = lpm_u8(bmp_header->data + current_data_offset + 1)))
      {
        case 0: /* End of Line */
                /* If line ends before the width of image, fill in with first entry in color table */
                show(strip);
                current_height += 1;
                current_width = 0;
                current_data_offset += 2;
                break;
        case 1: /* End of File */
                while(current_height < bmp_header->height && current_width < bmp_header->width)
                {
                  strip->pixels[current_width] = color_table[0];
                  if(current_width == bmp_header->width)
                  {
                    show(strip);
                    current_width = 0;
                    current_height += 1;
                  }
                  current_width += 1;
                }
                return;
        case 2: /* Delta */
                delta_width = current_width + lpm_u8(bmp_header->data + current_data_offset + 2);
                delta_height = current_height + lpm_u8(bmp_header->data + current_data_offset + 3);
                if(delta_width >= bmp_header->width)
                {
                  delta_width = 0;
                  delta_height += 1;
                }
                while(current_height != delta_height && current_width != delta_width)
                {
                  strip->pixels[current_width] = color_table[0];
                  current_width += 1;
                  if(current_width == bmp_header->width)
                  {
                    show(strip);
                    current_width = 0;
                    current_height += 1;
                  }
                }
                current_data_offset += 4;
                break;
        default:
                run_length = current_data>>1;
                run_counter = 0;
                current_data_offset += 2;
                while(run_counter < run_length)
                {
                  current_data = lpm_u8(bmp_header->data + current_data_offset + run_counter);
                  strip->pixels[current_width]      = color_table[(current_data >> 4)];
                  strip->pixels[current_width + 1]  = color_table[(current_data & 0x0F)];
                  run_counter++;
                  current_width += 2;
                }
                current_data_offset += run_length;
                break;

        }
      }
  }
}
