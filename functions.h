#include <avr/io.h>
#include <util/delay.h>

#include "uart.h"
#include "utils.h"

#include "ws2812_config.h" // override config in submodule
#include "light_ws2812.h"

// LED cRGB array ws2812 library reads periodically from
struct cRGB leds[LENGTH];

void delay_ms(int milliseconds);

void doSingleColor(color_t color);

void doBlink(uint16_t counter, uint16_t periode, color_t color, float dutycycle);

void doColorRotation(uint16_t rotation);

void doSlowFade(uint16_t stepsPerSecond, color_t color, uint8_t hardness);

int doStrobe(int min_time, int max_time, color_t color);

void chasingLights(int counter, uint8_t number, color_t color, color_t color_bg);

void rainbow();

void rotate(int counter);
