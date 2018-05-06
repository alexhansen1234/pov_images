#include "../../include/apa102.h"

void show(struct apa102 * strip)
{
  int i;
  display_pixel_apa102(0);
  for(i=0; i < strip->num_pixels; i++)
    display_pixel_apa102(0xE0000000 | ((uint32_t)strip->brightness) << 24 | strip->pixels[i]);
  display_pixel_apa102(0xFF);
}
