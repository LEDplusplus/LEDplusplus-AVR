# LEDplusplus-AVR

### LEDplusplus project's µC part written for AVR (Arduino Nano)

The LEDplusplus project has two main parts: 
* the server with a RESTful API and webinterface for controlling the LEDs and to send the commands via Bluetooth to the µC.
* the µC to receive the commands and controll the LEDs. 

We use a Arduino Nano as µC and HC-05 Bluetooth modules, to controll the ws2812(b) LED stripes.

Documentation of the commands the AVR accepts can be found [here](doc/commands.md)


### How to build and program

#### Summarized:

```shell
cd build/
make all
make program
```

#### Explained:

* Go to `build/` directory.
* `make all` compiles all `*.c` files from the parent folder and generated the `*.hex` files used to progam the AVRs flash and eeprom memory.
* `make program` uses *avrdude* the program the hex file containing the code into the Arduino microcontrollers flash.
* `make clean` removes all build outputs.

If you use Eclipse or another IDE you might want to use the `build/makefile` instead of auto-generating one.
