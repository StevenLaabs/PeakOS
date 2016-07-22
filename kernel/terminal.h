#ifndef _terminal_h
#define _terminal_h

#include <stddef.h>
#include <stdint.h>

void terminal_init();

void terminal_clear();
void terminal_write(char * str);
void terminal_putchar(char c);

void terminal_setcolor(uint8_t text, uint8_t background);

#endif
