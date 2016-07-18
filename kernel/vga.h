#ifndef _vga_h
#define _vga_h

#include <stdint.h>

#define VGA_BUFFER 0xB8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHT_GREY 7
#define DARK_GREY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_CYAN 11
#define LIGHT_RED 12
#define LIGHT_MAGENTA 13
#define LIGHT_BROWN 14
#define WHITE 15

static uint16_t* const VGA_PTR = (uint16_t*) 0xB8000;

static inline uint8_t get_color(uint8_t text, uint8_t background)
{
	return (background << 4) | text;
}

static inline uint16_t get_entry(char c, uint8_t color)
{
	uint16_t entry_color = color;
	uint16_t entry_char = c;

	return (entry_color << 8) | entry_char;
}

#endif