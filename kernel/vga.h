#ifndef _vga_h
#define _vga_h

#include <stdint.h>

#define VGA_BUFFER 0xB8000
#define VGA_SCREEN_WIDTH 80
#define VGA_SCREEN_HEIGHT 25

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

static uint16_t* const VGA_PTR = (uint16_t*) VGA_BUFFER;

static inline uint8_t vga_get_color(uint8_t text, uint8_t background)
{
	return (background << 4) | text;
}

static inline uint16_t vga_get_entry(char c, uint8_t color)
{
	uint16_t entry_color = color;
	uint16_t entry_char = c;

	return (entry_color << 8) | entry_char;
}

#endif
