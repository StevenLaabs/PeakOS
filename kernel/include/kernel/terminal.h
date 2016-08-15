#ifndef _TERMINAL_H
#define _TERMINAL_H

#include <stddef.h>
#include <stdint.h>

/*
 * Enables the cursor and sets the default terminal colors then clears the screen
 */
void terminal_init();

/*
 * Goes through all of the characters on the screen and clears them to null
 * values so the screen displays only the background color
 */
void terminal_clear();

/*
 * Scrolls the terminal screen by moving each character one row up from their
 * current positions
 */
void terminal_scroll();

/*
 * Writes a character string to the terminal
 */
void terminal_write(const char* str);

/*
 * Puts a single character in the terminal at the cursor position which is
 * relative to the VGA starting pointer
 */
void terminal_putchar(char c);

/*
 * Converts an integer with the given base value to a character
 * string which is then outputted to the terminal screen
 */
void terminal_writeint(int val, int base);

/*
 * Sets the foreground and background colors of the terminal for
 * the following write/clear commands
 */
void terminal_setcolor(uint8_t text, uint8_t background);

#endif
