#include <string.h>

void *memchr(const void *str, int ch, size_t count)
{
	unsigned char *ptr = (unsigned char *)str;
	
	while(count != 0)
	{
		if(*ptr != (unsigned char)ch)
			ptr++;
		
		else
			return ptr;

		count--;
	}

	return 0;
}
