/*#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
 
static void print(const char* data, size_t data_length)
{
	for ( size_t i = 0; i < data_length; i++ )
		putchar((int) ((const unsigned char*) data)[i]);
}
 
int printf(const char* restrict format, ...)
{
	va_list parameters;
	va_start(parameters, format);
 
	int written = 0;
	size_t amount;
	bool rejected_bad_specifier = false;
 
	while ( *format != '\0' )
	{
		if ( *format != '%' )
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
 
		if ( rejected_bad_specifier )
		{
		incomprehensible_conversion:
			rejected_bad_specifier = true;
			format = format_begun_at;
			goto print_c;
		}
 
		if ( *format == 'c' )
		{
			format++;
			char c = (char) va_arg(parameters, int);
			print(&c, sizeof(c));
		}
		else if ( *format == 's' )
		{
			format++;
			const char* s = va_arg(parameters, const char*);
			print(s, strlen(s));
		}
		else
		{
			goto incomprehensible_conversion;
		}
	}
 
	va_end(parameters);
 
	return written;
}*/

#include <stdio.h>
#include <stdarg.h>
#include <kernel/terminal.h>

int printf(const char* restrict format, ...)
{
	va_list args;
	va_start(args, format);

	const char * parse;
	unsigned int written = 0;
	int i;
	char *s;

	for(parse = format; *parse != '\0'; parse++)
	{
		if(*parse != '%')
		{
			asm("xchg bx, bx");
			putchar((int)(*parse));
			asm("xchg bx, bx");
			written++;
			continue;
		}

		parse++;

		switch(*parse)
		{
			case 'c':
				i = va_arg(args, int);
				putchar(i);
				break;

			case 's':
				s = va_arg(args, char*);
				puts(s);
				break;

			default:
				break;// err
		}
	}

	va_end(args);

	return written;
}
