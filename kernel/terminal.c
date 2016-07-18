#include "vga.h";

static size_t cursor_x;
static size_t cursor_y;

static unsigned char color;

void init_terminal() {
	cursor_pos = 0;

	set_background(BLUE);
	set_foreground(WHITE);

	clear_screen();
}

void clear_screen() {
	for(int i = 0; i < (SCREEN_WIDTH * SCREEN_HEIGHT); i++) {
		VGA_PTR[i] = (color << 8) 
	}
}

void set_background(unsigned char background) {
	color = (background << 4) | (0x0F & color);
}

void set_foreground(unsigned char color) {
	color = color | (0xF0 & color);
}