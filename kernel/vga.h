#ifndef _VGA_H
#define _VGA_H

#include <stdint.h>

// Starting point of the VGA text mode buffer address
#define VGA_BUFFER 0xC00B8000
#define VGA_SCREEN_WIDTH 80
#define VGA_SCREEN_HEIGHT 25

// Colors for the VGA text mode have these corresponding values
#define VGA_BLACK 0
#define VGA_BLUE 1
#define VGA_GREEN 2
#define VGA_CYAN 3
#define VGA_RED 4
#define VGA_MAGENTA 5
#define VGA_BROWN 6
#define VGA_LIGHT_GREY 7
#define VGA_DARK_GREY 8
#define VGA_LIGHT_BLUE 9
#define VGA_LIGHT_GREEN 10
#define VGA_LIGHT_CYAN 11
#define VGA_LIGHT_RED 12
#define VGA_LIGHT_MAGENTA 13
#define VGA_LIGHT_BROWN 14
#define VGA_WHITE 15

// Pointer to the start of the VGA text mode buffer
static uint16_t* const VGA_PTR = (uint16_t*) VGA_BUFFER;

/*
 * Makes a byte of the foreground and background colors where
 * the background is the first 4 bits and the foreground is the last 4
 */
static inline uint8_t vga_get_color(uint8_t text, uint8_t background)
{
	return (background << 4) | text;
}

/*
 * Creates a 2 byte entry that can be written to the VGA buffer with
 * the VGA color in the first byte and the ascii character in the second byte
 */
static inline uint16_t vga_get_entry(char c, uint8_t color)
{
	uint16_t entry_color = color;
	uint16_t entry_char = c;

	return (entry_color << 8) | entry_char;
}

#endif
