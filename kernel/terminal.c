#include "terminal.h"
#include "vga.h"
#include "io.h"

static size_t cursor_x;
static size_t cursor_y;

static uint8_t color;

static void enable_cursor() {
    outb(CURSOR_CMD_PORT, 0x0A);

    char scan_start = inb(CURSOR_DATA_PORT) & 0x1F; // scanline start

    outb(CURSOR_CMD_PORT, 0x0A);
    outb(CURSOR_DATA_PORT, scan_start | 0x20); // set cursor enabled
}

static void update_cursor()
{
	uint8_t position = (uint8_t)((cursor_y * 80) + cursor_x);
	outb(CURSOR_CMD_PORT, CURSOR_HIGH_BYTE);
	outb(CURSOR_DATA_PORT, (position & 0xFF));

	outb(CURSOR_CMD_PORT, CURSOR_LOW_BYE);
	outb(CURSOR_DATA_PORT, ((position >> 8) & 0xFF));
}

void terminal_init()
{
	cursor_x = 0;
	cursor_y = 0;

	enable_cursor();

	terminal_setcolor(VGA_WHITE, VGA_BLACK);

	terminal_clear();

	update_cursor();
}

void terminal_clear()
{
	for(int i = 0; i < (VGA_SCREEN_WIDTH * VGA_SCREEN_HEIGHT); i++)
	{
		VGA_PTR[i] = (color << 8);
	}
}

void terminal_scroll()
{
	for(int y = 0; y < VGA_SCREEN_HEIGHT; y++)
	{
		for(int x = 0; x < VGA_SCREEN_WIDTH; x++)
		{
			VGA_PTR[y * VGA_SCREEN_WIDTH + x] = VGA_PTR[(y+1) * VGA_SCREEN_WIDTH + x];
		}
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

void terminal_writeint(int val, int base)
{
	static char buf[32] = {0};

	int i = 30;

	for(; val && i ; --i, val /= base)

	buf[i] = "0123456789abcdef"[val % base];

	terminal_write(&buf[i+1]);
}

void terminal_putchar(char c)
{
	switch(c)
	{
		case '\n':
			cursor_x = 0;
			cursor_y++;
			break;

		case '\t':
			cursor_x += 4;
			if(cursor_x > VGA_SCREEN_WIDTH)
			{
				cursor_x = 4;
				cursor_y++;
			}
			break;

    case '\b':
      if(cursor_x == 0 && cursor_y == 0)
        break;

      if(cursor_x == 0)
      {
        cursor_y -= 1;
        cursor_x = VGA_SCREEN_WIDTH;
      }
      else
        cursor_x -= 1;

      VGA_PTR[cursor_y * VGA_SCREEN_WIDTH + cursor_x] = vga_get_entry(' ', color);
      break;

		default:
			VGA_PTR[cursor_y * VGA_SCREEN_WIDTH + cursor_x] = vga_get_entry(c, color);
			cursor_x++;
			if(cursor_x > VGA_SCREEN_WIDTH)
			{
				cursor_x = 0;
				cursor_y++;
			}
			break;
	}

	if(cursor_y > VGA_SCREEN_HEIGHT)
	{
		terminal_scroll();
		cursor_y = VGA_SCREEN_HEIGHT;
	}

	update_cursor();
}

void terminal_setcolor(uint8_t text, uint8_t background)
{
	color = vga_get_color(text, background);
}
