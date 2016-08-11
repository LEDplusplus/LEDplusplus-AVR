/*
 * uart.h
 */

#ifndef LEDPLUSPLUS_AVR_UART_UART_H_
#define LEDPLUSPLUS_AVR_UART_UART_H_

#define COMMAND_START 'S'
#define COMMAND_END 'E'
#define UART_MAX_COMMAND_LENGTH 10U

volatile uint8_t command[UART_MAX_COMMAND_LENGTH];
volatile uint8_t uart_rcv_complete;

/**
 * initializes the UART
 */
void uart_init();
/**
 * writes a char to the UART data register
 */
void uart_writechar(uint8_t data);

#endif /* LEDPLUSPLUS_AVR_UART_UART_H_ */
