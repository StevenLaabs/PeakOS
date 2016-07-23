#include <stdio.h>
#include <stdarg.h>

int printf(const char *format, ...)
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
			putchar((int)(*parse));
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
