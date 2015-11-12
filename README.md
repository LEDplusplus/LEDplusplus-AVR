# LEDplusplus-AVR

### LEDplusplus project's µC part written for AVR (Arduino Nano)

The LEDplusplus project has two main parts: 
* the server with a RESTful API and webinterface for controlling the LEDs and to send the commands via Bluetooth to the µC.
* the µC to receive the commands and controll the LEDs. 

We use a Arduino Nano as µC and HC-05 Bluetooth modules, to controll the ws2812(b) LED stripes.
