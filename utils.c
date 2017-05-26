#include "utils.h"

// rotates trough (hsv) color space, returns a rgb color struct
color_t colorRotation(uint16_t rotation) {
  color_t color;
  	// Convert HSV (h = rotation, s = 255, v = 255; saturation and lightness not regarded)
  	uint8_t section, section_rotation;
  	uint16_t q, t;
  	section = (rotation % 360) / 43;
  	section_rotation = (rotation % 360) % 43;
  	// p = 0;
  	q = (255 * ((10710 - (255 * section_rotation)) / 42)) / 256;
  	t = (255 * ((10710 - (255 * (42 - section_rotation))) / 42)) / 256;
  	switch (section) {
  	case 0:
  		color.r = 255;
  		color.g = t;
  		color.b = 0;
  		break;
  	case 1:
  		color.r = q;
  		color.g = 255;
  		color.b = 0;
  		break;
  	case 2:
  		color.r = 0;
  		color.g = 255;
  		color.b = t;
  		break;
  	case 3:
  		color.r = 0;
  		color.g = q;
  		color.b = 255;
  		break;
  	case 4:
  		color.r = t;
  		color.g = 0;
  		color.b = 255;
  		break;
  	case 5:
  		color.r = 255;
  		color.g = 0;
  		color.b = q;
  		break;
  	default:
      color.r = 0;
      color.g = 0;
      color.b = 0;
  		break;
    }
  return color;
}
