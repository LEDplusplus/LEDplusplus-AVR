#ifndef LEDPLUSPLUS_AVR_UTIL_H_
#define LEDPLUSPLUS_AVR_UTIL_H_

#ifndef LENGTH
  #define LENGTH 33
#endif

#include <avr/io.h>
#include "color.h"

color_t colorRotation(uint16_t rotation);

#endif
