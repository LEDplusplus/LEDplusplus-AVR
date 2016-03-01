/*
 * main.c
 *
 *  Created on: 12.11.2015
 *      Author: Leonard and Raphael
 */

#ifndef LENGTH
#define LENGTH 30
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdlib.h>

#include "ws2812_config.h" // override config in submodule
#include "Light_WS2812/light_ws2812.h"

// LED cRGB array ws2812 library reads periodically from
struct cRGB leds[LENGTH];

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


// variable delay
void delay_ms(int milliseconds) {
	while(--milliseconds){
		_delay_us(1000);
	}
}
void doSingleColor(uint8_t r, uint8_t g, uint8_t b) {
	for (uint8_t i = 0; i < LENGTH; i++) {
		leds[i].r = r;
		leds[i].g = g;
		leds[i].b = b;
	}
}


// blink adjustable duty cycle
void doBlink(uint16_t counter, uint16_t periode, uint8_t r, uint8_t g, uint8_t b, float dutycycle) {
	if ((counter % periode) == 0) {
		doSingleColor(0, 0, 0);
	}
	else if ((counter % periode) == (uint16_t)(dutycycle*periode)) {
		doSingleColor(r, g, b);
	}
}


void doColorRotation(uint16_t rotation) {
	// Convert HSV (h = rotation, s = 255, v = 255; saturation and lightness not regarded)
	uint8_t r, g, b;
	uint8_t section, section_rotation;
	uint16_t q, t;
	section = (rotation % 360) / 43;
	section_rotation = (rotation % 360) % 43;
	// p = 0;
	q = (255 * ((10710 - (255 * section_rotation)) / 42)) / 256;
	t = (255 * ((10710 - (255 * (42 - section_rotation))) / 42)) / 256;
	switch (section) {
	case 0:
		r = 255;
		g = t;
		b = 0;
		break;
	case 1:
		r = q;
		g = 255;
		b = 0;
		break;
	case 2:
		r = 0;
		g = 255;
		b = t;
		break;
	case 3:
		r = 0;
		g = q;
		b = 255;
		break;
	case 4:
		r = t;
		g = 0;
		b = 255;
		break;
	case 5:
		r = 255;
		g = 0;
		b = q;
		break;
	}

	for (uint8_t i = 0; i < LENGTH; i++) {
		leds[i].r = r;
		leds[i].g = g;
		leds[i].b = b;
	}
}

void doSlowFade (uint16_t stepsPerSecond, uint8_t r, uint8_t g, uint8_t b, uint8_t hardness) {
	doSingleColor(r/100*hardness, g/100*hardness, b/100*hardness);
	delay_ms((int)1000/stepsPerSecond);
}

// do strobe with maximal and minimal period time in ms
// and predefined or random (0, 0, 0) color
void doStrobe (int min_time, int max_time, int r, int g, int b) {
	// random time on
	int on = (rand() % (max_time - min_time)) + min_time;
	// random time off
	int off = (rand() % (max_time - min_time)) + min_time;
	// random rgb, if not defined
	if ((r==0) && (g==0) && (b==0)) {
		r = (rand() % 255);
		g = (rand() % 255);
		b = (rand() % 255);
	}
	doSingleColor(r, g, b);
	ws2812_setleds(leds, LENGTH);
	delay_ms(on);
	doSingleColor(0, 0, 0);
	ws2812_setleds(leds, LENGTH);
	delay_ms(off);

}


int main(void) {

	_delay_ms(1000);

	DDRD = (1 << PD7); // PD7 (ws2812 data out) as output
	// led (arduino pin 13 / PB5) for debugging
	DDRB = (1 << PB5); // PB5 as output
	 PORTB = (1 << PB5); // PB5 on

	uint16_t counter = 0;

	// 1 second R - G - B as 'start signal'
	doSingleColor(255, 0, 0);
	ws2812_setleds(leds, LENGTH);
	_delay_ms(1000);
	doSingleColor(0, 255, 0);
	ws2812_setleds(leds, LENGTH);
	_delay_ms(1000);
	doSingleColor(0, 0, 255);
	ws2812_setleds(leds, LENGTH);
	_delay_ms(1000);

	// uint8_t hardness = 0;

	 while(1) {
		counter++;
		//_delay_us(800);
		//////////////////////
		//doColorRotation(counter);
		//////////////////////
		//doBlink(counter, 900, 0, 0, 150, 0.5);
		/////////////////////
		//doSlowFade(5, 255, 255, 255, hardness);
		//if (hardness < 100) {
		//	hardness++;
		//}
		// Refresh LED strip every loop
		// ws2812_setleds(leds, LENGTH);
		/////////////////////////
		doStrobe(100, 300, 0, 0, 0);
		// toggle led for debugging
		PORTB ^= (1 << PB5);
	}
}
