#ifndef _IO_H
#define _IO_H

#include <stdint.h>

// Outputs the value argument to the given port address using the out instruction
void outb(uint16_t port, uint8_t value);

// Receives input at the given port address using the in instruction then returns the value
uint8_t inb(uint16_t port);

#endif
