#include <avr/io.h>
#include <stdlib.h>

typedef struct color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} color_t;

color_t color_black = {0, 0, 0};

color_t color_r = {255, 0, 0};

color_t color_g = {0, 255, 0};

color_t color_b = {0, 0, 255};
