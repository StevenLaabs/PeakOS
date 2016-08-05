#ifndef _DE9_H
#define _DE9_H

#include <stdint.h>

// Address definitions of the COM ports
#define COM1 0x3F8
#define COM2 0x2F8
#define COM3 0x3E8
#define COM4 0x2E8

/*
 * Initializes the designated com port (COM1-COM4) with the default baud rate and
 * default line, buffer, and modem configurations define in the config methods.
 */
void de9_init(uint16_t com);

/*
 * Sets the baud rate of the COM port to 115200 divided by the divisor argument
 * by enabling the DLAB bit and outputting the low and high bytes for the divisor
 * Note: This means the line control register needs to be reset when the baud rate is
 * configured
 */
void de9_set_baud(uint16_t com, uint16_t divisor);

/*
 * Configures the serial line with default values of an 8-bit length, no parity,
 * one stop bit, and break control disabled
 */
void de9_config_line(uint16_t com);

/*
 * Configures the serial buffer with FIFO enabled and 14 byte size
 */
void de9_config_buffer(uint16_t com);

/*
 * Configures the serial modem register to have IRQs enabled with the RTS and DTR
 * bits set. This configures the serial port to do both read and write operations.
 */
void de9_config_modem(uint16_t com);

/*
 * Waits for input through the serial port and reads in the input which is then
 * returned as a char value
 */
char read_serial(uint16_t com);

/*
 * Waits for the serial port to be ready to transmit then sends the passed char
 * value out through the serial port
 */
void write_serial(uint16_t com, char c);

#endif
