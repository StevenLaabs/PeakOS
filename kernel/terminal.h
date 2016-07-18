#ifndef _terminal_h
#define _terminal_h

void init_terminal();

void clear_screen();
void terminal_write();
void terminal_putchar(unsigned char c);

void set_background();
void set_foreground();

#endif