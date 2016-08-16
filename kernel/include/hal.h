#ifndef _HAL_H
#define _HAL_H

#include <stdint.h>

typedef void (*handler_func_t)(void);

void hal_init();

void enable_interrupts();
void disable_interrupts();

void irq_install(uint8_t irq_num, void (*handler)());

void interrupt_complete(uint8_t irq_num);

#endif