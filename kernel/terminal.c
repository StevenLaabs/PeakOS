#include "terminal.h"
#include "vga.h"

static size_t cursor_x;
static size_t cursor_y;

static uint8_t color;

void terminal_init()
{
	cursor_x = 0;
	cursor_y = 0;

	terminal_setcolor(VGA_WHITE, VGA_BLUE);

	terminal_clear();
}

void terminal_clear()
{
	for(int i = 0; i < (VGA_SCREEN_WIDTH * VGA_SCREEN_HEIGHT); i++) 
	{
		VGA_PTR[i] = (color << 8);
	}
}

void terminal_write(char * str)
{
	int index = 0;
	while(str[index] != '\0')
	{
		terminal_putchar(str[index++]);
	}
}

void terminal_putchar(char c)
{
	VGA_PTR[cursor_y * VGA_SCREEN_WIDTH + cursor_x] = vga_get_entry(c, color);
	
	cursor_x++;

	if(cursor_x > VGA_SCREEN_WIDTH)
	{
		cursor_x = 0;
		cursor_y++;

		if(cursor_y > VGA_SCREEN_HEIGHT)
		{
			// scroll screen
		}
	}
}

void terminal_setcolor(uint8_t text, uint8_t background)
{
	color = vga_get_color(text, background);
}
