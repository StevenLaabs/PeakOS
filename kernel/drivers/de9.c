#include <hal.h>
#include <drivers/de9.h>

#define DIVISOR_LOW 0
#define DIVISOR_HIGH 1

#define DATA_REG 0
#define INT_REG 1
#define BUFFER_REG 2
#define LINE_CTRL_REG 3
#define MODEM_CTRL_REG 4
#define LINE_STATUS_REG 5
#define MODEM_STATUS_REG 6
#define SCRATCH_REG 7

#define DLAB_ENABLE 0x80

void de9_set_baud(uint16_t com, uint16_t divisor)
{
	outb(com + INT_REG, DLAB_ENABLE);                  // set the DLAB bit to configure baud rate
	outb(com + DIVISOR_LOW, divisor & 0x00FF);         // set lowest 8 bits of divisor
	outb(com + DIVISOR_HIGH, (divisor >> 8) & 0x00FF); // set highest 8 bits of divisor
}

void de9_config_line(uint16_t com)
{
	// 0x03: 8 bit length with no parity, one stop bit, and no break control
	outb(com + LINE_CTRL_REG, 0x03);
}

void de9_config_buffer(uint16_t com)
{
	// 0xC7: Enable FIFO, clear receiver/transmission FIFO queues, 14 bytes for size
	outb(com + BUFFER_REG, 0xC7);
}

void de9_config_modem(uint16_t com)
{
	// 0x0B: IRQ enabled, ready to send and data terminal ready set
	outb(com + MODEM_CTRL_REG, 0x0B);
}

// Returned the state of the received bit to determine if the serial port has received data
static int serial_received(uint16_t com)
{
	return inb(com + LINE_STATUS_REG) & 1;
}

char read_serial(uint16_t com)
{
	while(serial_received(com) == 0) {}

	return inb(com);
}

// Returns whether the transmission bit is set to determine if there is space to transmit
static int is_transmit_empty(uint16_t com)
{
	return inb(com + LINE_STATUS_REG) & 0x20;
}

void write_serial(uint16_t com, char c)
{
	while(is_transmit_empty(com) == 0) {}

	outb(com, c);
}

void de9_init(uint16_t com)
{
	outb(com + INT_REG, 0x00); // disable all interrupt registers
	de9_set_baud(com, 0x0003);
	de9_config_line(com);
	de9_config_buffer(com);
	de9_config_modem(com);
}
