#include "../../include/apa102.h"

void push_pixel(struct apa102 * strip, uint32_t rgb_data, uint32_t i)
{
  display_pixel_apa102(0xE0000000 | ((uint32_t)strip->brightness) << 24 | strip->pixels[i]);
}
