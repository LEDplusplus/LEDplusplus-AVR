TARGET = main
MCU = atmega328p

PROGRAMMER = arduino
# Auskommentieren für automatische Wahl
PORT = -P /dev/serial/by-id/usb-1a86_USB2.0-Serial-if00-port0
BAUD = -b 57600

VPATH = ..

RAWSOURCES = $(wildcard ../*.c)
RAWSOURCES += ../../light_ws2812/light_ws2812.c
SOURCES = $(RAWSOURCES:../%=%)
OBJECTS = $(SOURCES:.c=.o)

TARGET_EEPROM = $(TARGET)_eeprom

CFLAGS = -c -Os -g2 -gstabs -std=gnu11 -Wall
## Use short (8-bit) data types
CFLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
## Splits up object files per function
CFLAGS += -ffunction-sections -fdata-sections
## more cflags
CFLAGS += -DF_CPU=16000000UL

LDFLAGS = -Wl,-Map,$(TARGET).map,--cref -mrelax
## Optional, but often ends up with smaller code
LDFLAGS += -Wl,--gc-sections

.PHONY = clean size program

all: hex eeprom size

hex: $(TARGET).hex

eeprom: $(TARGET_EEPROM).hex

$(TARGET).hex: $(TARGET).elf
	avr-objcopy -O ihex -j .data -j .text $(TARGET).elf $(TARGET).hex

$(TARGET_EEPROM).hex: $(TARGET).elf
	avr-objcopy -O ihex -j .eeprom --change-section-lma .eeprom=1 $(TARGET).elf $(TARGET_EEPROM).hex

$(TARGET).elf: $(OBJECTS)
	avr-gcc $(LDFLAGS) -mmcu=$(MCU) $(OBJECTS) -o $(TARGET).elf

%.o: %.c
	avr-gcc $(CFLAGS) -mmcu=$(MCU) $< -o $@

size: $(TARGET).elf
	avr-size --mcu=$(MCU) -C $(TARGET).elf

program: all
	avrdude -p$(MCU) $(PORT) $(BAUD) -c$(PROGRAMMER) -Uflash:w:$(TARGET).hex:a

clean:
	rm -rf *.o
	rm -rf *.elf
	rm -rf *.hex
	rm -rf *.map
