#include <avr/io.h>
#include <stdlib.h>

#ifndef LEDPLUSPLUS_AVR_COLOR_H_
#define LEDPLUSPLUS_AVR_COLOR_H_

// color struct with rgb values
typedef struct color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} color_t;

#endif
