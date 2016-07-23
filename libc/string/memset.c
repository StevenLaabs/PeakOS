#include <string.h>

void *memset(void *dest, int ch, size_t count)
{
	unsigned char *ptr = (unsigned char *)dest;
	
	for(unsigned int i = 0; i < count; i++)
	{
		ptr[i] = (unsigned char)ch;
	}

	return dest;
}
