/*
 * main.c
 *
 *  Created on: 12.11.2015
 *      Author: Leonard and Raphael
 */

#ifndef F_CPU
 #define F_CPU 16000000UL
#endif

#include <avr/interrupt.h>

#include "functions.h"

// main function, coordinats the program flow
int main(void) {
	// initialize UART
	uart_init();
	uint16_t doStrobe_next_call = 0;

  color_t color_red = {255, 0, 0};
  color_t color_green = {0, 255, 0};
  color_t color_blue = {0, 0, 255};

	_delay_ms(1000);

	DDRD = (1 << PD7); // PD7 (ws2812 data out) as output
	// led (arduino pin 13 / PB5) for debugging
	DDRB = (1 << PB5); // PB5 as output
	PORTB = (1 << PB5); // PB5 on

	uint16_t counter = 0;

	// 1 second R - G - B as 'start signal'
	doSingleColor(color_red);
	ws2812_setleds(leds, LENGTH);
	_delay_ms(1000);
	doSingleColor(color_green);
	ws2812_setleds(leds, LENGTH);
	_delay_ms(1000);
	doSingleColor(color_blue);
	ws2812_setleds(leds, LENGTH);
	_delay_ms(1000);

  rainbow();

	// uint8_t hardness = 0;

	while (1) {
    /**
		// handle UART command
		if (uart_rcv_complete == 1) {
			switch(command[0]) {
				case 'r':
					doSingleColor(255, 0, 0);
					break;
				case 'g':
					doSingleColor(0, 255, 0);
					break;
				case 'b':
					doSingleColor(0, 0, 255);
					break;
			}

		}**/
		// delay 800 µs -> loop needs ~1ms per iteration
		_delay_us(8000);
		//////////////////////
		//doColorRotation(counter);
		//////////////////////
		//doBlink(counter, 900, 0, 0, 150, 0.5);
		/////////////////////
		//doSlowFade(5, 255, 255, 255, hardness);
		//if (hardness < 100) {
		//	hardness++;
		//}
		/////////////////////////
		// only call doStrobe, if counter is equal to the time,
		// the function wants to be called again
		//if (counter == doStrobe_next_call) {
		//	doStrobe_next_call = doStrobe(100, 300, 0, 0, 0) + counter;
		//}
    //chasingLights(counter, 5, 255, 0, 0, 0, 0, 255);
    ////////////////////////
    rotate(counter);
		// Refresh LED strip every loop
		ws2812_setleds(leds, LENGTH);
		// toggle led for debugging
		PORTB ^= (1 << PB5);
		counter++;
	}
}
