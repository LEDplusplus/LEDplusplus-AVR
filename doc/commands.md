# Documentation for LEDpp-AVR

#### Warning

This documentation describes the developing purpose, not the current status, so some functions may not be implemented yet.

## Command structure

| Startbyte |  commmand   |    parameters        |  Endbyte   |
|-----------|-------------|----------------------|------------|
| char: 'S' | char: a-z   |    int8 / int16      | char: 'E'  |

Every parameter is ASCII coded (decimal) and seperated by whitespaces.

Parameters have fixed length depending on type and must be zero-filled:

* int8: unsigned, 3 decimal places, maximum: 255
* int16: unsigned, 5 decimal places, maximum: 65535


## commands for entire LED Array

### Single color:

All LEDs have the same color

command: 'a'

| Parameters | r    | g    | b    |
|------------|------|------|------|
| Type       | int8 | int8 | int8 |

example: `a 255 255 255` for white color



### Blink:

All LEDs have the same color, blinking with periodical with an off-time

command: 'b'

| Parameters | r    | g    | b    | period length / ms | off-time / % |
|------------|------|------|------|--------------------|--------------|
| Type       | int8 | int8 | int8 | int16              | int8         |

example: `b 255 000 000 02000 050` for blinking in red color periodical every 2000 ms with 50% off-time



### Color rotation

All LEDs have the same color, rotationg periodical trough color space

command: 'c'

| Parameters | period length |
|------------|---------------|
| Type       | int8          |

example: `c 050` for one rotation through color space in 5s



### Fade on

Fades all LEDs slowly from off to the same color

command: 'd'

| Parameters | r    | g    | b    | fade duration / ms |
|------------|------|------|------|--------------------|
| Type       | int8 | int8 | int8 | int16              |

example: `d 000 255 000 05000` fades to red color in 5 seconds



### Fade off

Fades all LEDs off

command: 'e'

| Parameters | fade duration / ms |
|------------|--------------------|
| Type       | int16              |

example: `e 05000` fades to red color in 5 seconds



### Strobe

Strobes with random or predefined color and random period between min and max time in ms

command: 'f'

| Parameters | r    | g    | b    | min period / ms | max period / ms |
|------------|------|------|------|-----------------|-----------------|
| Type       | int8 | int8 | int8 | int16           | int16           |

Zero in r, g and b activates random color mode.

example 1: `f 000 000 000 00200 01200` strobe with random color and period between 200ms and 1200ms

example 2: `f 200 000 000 00500 00500` strobe with red color and period of 500ms




## commands for single LEDs

### single LEDS

Set the color of single LEDs

command: 'n'

| Parameters | r    | g    | b    | position (zero based) |
|------------|------|------|------|-----------------------|
| Type       | int8 | int8 | int8 | int8                  |

example: `n 255 255 255 010` switches the 11th LED on (white)



### chaser light

Periodical chaser light with background color

command: 'o'

| Parameters | r    | g    | b    | r (BG) | g (BG) | b (BG) | number of chasing leds | float period / ms |
|------------|------|------|------|--------|--------|--------|------------------------|-------------------|
| Type       | int8 | int8 | int8 | int8   | int8   | int8   | int8                   | int16             |

BG: Background

example: `o 255 000 000 000 255 000 005 03000` 5 red chasing Light LEDs on green background, need 3 seconds for run-through
