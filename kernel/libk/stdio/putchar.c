#include <stdio.h>
#include <kernel/terminal.h>

int putchar(int ch)
{
	char c = (char)ch;
	terminal_putchar(c);
	
	return ch;
}
