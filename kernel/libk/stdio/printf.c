#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <kernel/terminal.h>

static void print(const char* data, size_t data_length)
{
	for ( size_t i = 0; i < data_length; i++ )
		putchar((int) ((const unsigned char*) data)[i]);
}
 
int printf(const char* restrict format, ...)
{
	va_list args;
	va_start(args, format);

	unsigned int written = 0;

	size_t amount;
	bool bad_specifier = false;
 
	while ( *format != '\0' )
	{
		if (bad_specifier || *format != '%' )
		{
		print_c:
			amount = 1;
			while ( format[amount] && format[amount] != '%' )
				amount++;
			print(format, amount);
			format += amount;
			written += amount;
			continue;
		}
 
		const char* format_begun_at = format;
 
		if ( *(++format) == '%' )
			goto print_c;
 
		switch(*format)
		{
			case 'c': {
				format++;
				int c = va_arg(args, int);
				putchar(c);
				written++;
				break;
			}

			case 's': {
				format++;
				const char* s = va_arg(args, const char*);
				int len = strlen(s);
				print(s, len);
				written += len;
				break;
			}

			case 'd':
			case 'i': {
				format++;
				int i = va_arg(args, int);
				char str[20];
				itoa_signed(i, str, 10);
				int len = strlen(str);
				print(str, len);
				written += len;
				break;
			}

			case 'u': {
				format++;
				int i = va_arg(args, unsigned int);
				char str[20];
				itoa(i, str, 10);
				int len = strlen(str);
				print(str, len);
				written += len;
				break;
			}

			case 'x': {
				format++;
				int x = va_arg(args, int);
				char* str;
				itoa(x, str, 16);
				int len = strlen(str);
				print(str, len);
				written += len;
				break;
			}

			default:
				bad_specifier = true;
				format = format_begun_at;
		}
	}
 
	va_end(args);
 
	return written;
}
