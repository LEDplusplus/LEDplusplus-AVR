# Documentation for LEDpp-AVR

## Warning

This documentation describes the developing purpose, not the cuzrrent status, so some functions may not be implemented yet.

## Command structure

| Startbyte |  commmand   |    parameters        |  Endbyte   |
|-----------|-------------|----------------------|------------|
| char: 'S' | char: a-z   | byte / int / float   | char: 'E'  |


## commands for entire LED Array

### Single color:

All LEDs have the same color

command: 'a'

values: byte r, byte g, byte b

example: `a 255 255 255` for white color



### Blink:

All LEDs have the same color, blinking with periodical with an off-time

command: 'b'

values: byte r, byte g, byte g, byte b, byte periode, float off-time (0-1)

example: `b 255 0 0 20 0.5` for blinking in red color periodical every 20 time units with 50% off-time



### Color rotation

All LEDs have the same color, rotationg periodical trough color space

command: 'c'

values: byte speed

example: `c 50` for one rotation through color space in 50 time units



### Slow fade

Fades all LEDs slowly from off to the same color

command: 'd'

values: byte r, byte g, byte b, byte seconds

example: `0 255 0 5` fades to red color in 5 seconds



### Strobe

Strobes with random or predefined color and random period between min and max time in ms

command: 'e'

values: byte r, byte g, byte b, int min time, int max time

example 1: `0 0 0 200 1200` strobe with random color and period between 200ms and 1200ms

example 2: `200 0  0 500 500` strobe with red color and period of 500ms 



## commands for single LEDs

### single LEDS

Set the color of single LEDs

command: 'n'

values: byte r, byte g, byte b, byte position (0 based)

example: `255 255 255 10` switches the 11th LED on (white)



### chaser light

Periodical chaser light with background color

command: 'o'

values: byte r, byte g, byte b, byte r, byte g, byte g, byte numer chasing leds, float period in s

example: `255 0 0 0 255 0 5 3.0` 5 red chasing Light LEDs on green background, need 3 seconds for run-through