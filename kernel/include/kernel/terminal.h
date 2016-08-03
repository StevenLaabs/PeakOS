#ifndef _TERMINAL_H
#define _TERMINAL_H

#include <stddef.h>
#include <stdint.h>

#define CURSOR_CMD_PORT 0x3D4
#define CURSOR_DATA_PORT 0x3D5
#define CURSOR_LOW_BYTE 0x0F
#define CURSOR_HIGH_BYTE 0x0E

void terminal_init();

void terminal_clear();
void terminal_scroll();

void terminal_write(char * str);
void terminal_putchar(char c);
void terminal_writeint(int val, int base);

void terminal_setcolor(uint8_t text, uint8_t background);

#endif
