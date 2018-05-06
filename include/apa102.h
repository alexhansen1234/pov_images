#include <stdint.h>

#ifndef APA102_H
  #define APA102_H
  struct apa102
  {
    uint8_t     num_pixels;
    uint8_t     port;
    uint8_t     data_bit;
    uint8_t     clk_bit;
    uint8_t     brightness;
    uint32_t  * pixels;
  };


  extern void display_pixel_apa102(uint32_t data);
  extern void show(struct apa102 * strip);
  extern void push_pixel(struct apa102 * strip, uint32_t rgb_data, uint32_t index);

  /*
  void show(struct apa102 * strip)
  {
    int i;
    display_pixel_apa102(0);
    for(i=0; i < strip->num_pixels; i++)
      display_pixel_apa102(0xE0000000 | ((uint32_t)strip->brightness) << 24 | strip->pixels[i]);
    display_pixel_apa102(0xFF);
  }
  */
  /*
  void push_pixel(struct apa102 * strip, uint32_t rgb_data, uint32_t i)
  {
    display_pixel_apa102(0xE0000000 | ((uint32_t)strip->brightness) << 24 | strip->pixels[i]);
  }
  */

#endif
