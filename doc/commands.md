# Documentation for LEDpp-AVR

## Warning

This documentation describes the developing purpose, not the current status, so some functions may not be implemented yet.

## Command structure

| Startbyte |  commmand   |    parameters        |  Endbyte   |
|-----------|-------------|----------------------|------------|
| char: 'S' | char: a-z   |      int / float     | char: 'E'  |

Everything is ASCII coded, all values are seperated by whitespaces.


## commands for entire LED Array

### Single color:

All LEDs have the same color

command: 'a'

values:  r, g, b

example: `a 255 255 255` for white color



### Blink:

All LEDs have the same color, blinking with periodical with an off-time

command: 'b'

values: r, g, g, b, periode length in ms, off-time in percent (0-100)

example: `b 255 000 000 02000 050` for blinking in red color periodical every 2000 ms with 50% off-time



### Color rotation

All LEDs have the same color, rotationg periodical trough color space

command: 'c'

values: periode length

example: `c 050` for one rotation through color space in 5s



### Fade on

Fades all LEDs slowly from off to the same color

command: 'd'

values: r, g, b, seconds / 10

example: `d 000 255 000 050` fades to red color in 5 seconds



### Fade off

Fades all LEDs off

command: 'e'

values: time in ms

example: `d 000 255 000 05000` fades to red color in 5 seconds



### Strobe

Strobes with random or predefined color and random period between min and max time in ms

command: 'f'

values: r, g, b, int min time, int max time

example 1: `e 000 000 000 200 1200` strobe with random color and period between 200ms and 1200ms

example 2: `e 200 000 000 500 500` strobe with red color and period of 500ms 




## commands for single LEDs

### single LEDS

Set the color of single LEDs

command: 'n'

values: r, g, b, position (0 based)

example: `n 255 255 255 010` switches the 11th LED on (white)



### chaser light

Periodical chaser light with background color

command: 'o'

values: r, g, b, r, g, g, number of chasing leds, float period in s

example: `o 255 000 000 000 255 000 005 3.0` 5 red chasing Light LEDs on green background, need 3 seconds for run-through
