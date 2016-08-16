#ifndef _HAL_H
#define _HAL_H

#include <stdint.h>

// Initializes the HAL which includes the IDT and PIC setup
void hal_init();

// Calls the sti instruction for enabling interrupts
void enable_interrupts();

// Calls the cli instruction for disabling interrupts
void disable_interrupts();

// Installs the handler method for an IRQ
void irq_install(uint8_t irq_num, void (*handler)());

// Sends an end of interrupt signal on completion of an IRQ
void interrupt_complete(uint8_t irq_num);

// Outputs the value argument to the given port address using the out instruction
void outb(uint16_t port, uint8_t value);

// Receives input at the given port address using the in instruction then returns the value
uint8_t inb(uint16_t port);

#endif