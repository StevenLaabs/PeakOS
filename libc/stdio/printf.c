#include <stdio.h>

static void print(const char* data, size_t length)
{
	for(unsigned int i = 0; i < length; i++)
	{
		putchar((int)((const unsigned char *)data)[i]);
	}
}

int printf(const char *format, ...)
{
	// do printf	
}
