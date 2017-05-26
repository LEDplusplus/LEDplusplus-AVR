#include "functions.h"
#include <avr/pgmspace.h>

// gamma corrected warm white light (64 steps)
const uint8_t blind_r[64] PROGMEM = { 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44,
		48, 52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92, 96, 100, 104, 108, 112,
		116, 120, 124, 128, 131, 135, 139, 143, 147, 151, 155, 159, 163, 167,
		171, 175, 179, 183, 187, 191, 195, 199, 203, 207, 211, 215, 219, 223,
		227, 231, 235, 239, 243, 247, 251, 255 };
const uint8_t blind_g[64] PROGMEM = { 1, 3, 4, 6, 7, 8, 10, 11, 13, 14, 15, 17,
		18, 20, 21, 23, 24, 25, 27, 28, 30, 31, 32, 34, 35, 37, 38, 39, 41, 42,
		44, 45, 46, 48, 49, 51, 52, 53, 55, 56, 58, 59, 60, 62, 63, 65, 66, 68,
		69, 70, 72, 73, 75, 76, 77, 79, 80, 82, 83, 84, 86, 87, 89, 90 };
const uint8_t blind_b[64] PROGMEM = { 0, 1, 1, 2, 2, 2, 3, 3, 4, 4, 4, 5, 5, 5,
		6, 6, 7, 7, 7, 8, 8, 9, 9, 9, 10, 10, 11, 11, 11, 12, 12, 13, 13, 13,
		14, 14, 14, 15, 15, 16, 16, 16, 17, 17, 18, 18, 18, 19, 19, 20, 20, 20,
		21, 21, 21, 22, 22, 23, 23, 23, 24, 24, 25, 25 };

color_t color_black = {0, 0, 0};

// variable delay
void delay_ms(int milliseconds) {
	while(--milliseconds){
		_delay_us(1000);
	}
}

// all LEDs the same color
void doSingleColor(color_t color) {
	for (uint8_t i = 0; i < LENGTH; i++) {
		leds[i].r = color.r;
		leds[i].g = color.g;
		leds[i].b = color.b;
	}
}

// blink adjustable duty cycle
void doBlink(uint16_t counter, uint16_t periode, color_t color, float dutycycle) {
	if ((counter % periode) == 0) {
		doSingleColor(color_black);
	} else if ((counter % periode) == (uint16_t) (dutycycle * periode)) {
		doSingleColor(color);
	}
}

// rotate trough color space, all LEDs have the same color
void doColorRotation(uint16_t rotation) {

  color_t color = colorRotation(rotation);

	for (uint8_t i = 0; i < LENGTH; i++) {
		leds[i].r = color.r;
		leds[i].g = color.g;
		leds[i].b = color.b;
	}
}

// slowly fade the LEDs (all the same color) with variable steps and hardness
void doSlowFade(uint16_t stepsPerSecond, color_t color, uint8_t hardness) {
  color.r /= (100 * hardness);
  color.g /= (100 * hardness);
  color.b /= (100 * hardness);
	doSingleColor(color);
	delay_ms((int) 1000 / stepsPerSecond);
}

/*Strobe with maximal and minimal period time in ms
 and predefined or random (0, 0, 0) color.
 For periodical strobe set min_time = max_time.
 Returns time in ms until doStrobe wants to be called next time. */
int doStrobe(int min_time, int max_time, color_t color) {
	// time until next function call
	int next_call;
	// 0 = off, 1 = on
	static int on_off = 0;
	if (on_off == 0) {
		// random rgb, if not define
		if ((color.r == 0) && (color.g == 0) && (color.b == 0)) {
			color.r = (rand() % 255);
			color.g = (rand() % 255);
			color.b = (rand() % 255);
		}
		doSingleColor(color);
		on_off = 1;
	} else {
		doSingleColor(color_black);
		on_off = 0;
	}
	// if time should not be periodic -> random time on / off
	if (min_time != max_time) {
		next_call = (rand() % (max_time - min_time)) + min_time;
	} else {
		next_call = min_time;
	}
	return next_call;
}

// chasing lights, adjustable colors for chasing lights and background, variable number of chasing light LEDs
void chasingLights(int counter, uint8_t number, color_t color, color_t color_bg) {
  doSingleColor(color_bg);
  uint8_t i = 0;
  for(i = 0; i < number; i++) {
    leds[counter%LENGTH+i].r = color.r;
    leds[counter%LENGTH+i].g = color.g;
    leds[counter%LENGTH+i].b = color.b;
  }
}

// gardient through all colors, whole LED strip
void rainbow() {
  int i;
  uint16_t rotation;
  for( i = 0; i < LENGTH; i++) {
    rotation = (360 / LENGTH) * i;
    color_t color = colorRotation(rotation);
    leds[i].r = color.r;
    leds[i].g = color.g;
    leds[i].b = color.b;
  }
}

// rotate a given pattern
void rotate(int counter) {
  leds[counter%LENGTH].r = leds[(counter+1)%LENGTH].r;
  leds[counter%LENGTH].g = leds[(counter+1)%LENGTH].g;
  leds[counter%LENGTH].b = leds[(counter+1)%LENGTH].b;
}
