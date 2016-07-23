#include <string.h>

void *memcpy(void *dest, const void *src, size_t count)
{
	unsigned char *tempd = (unsigned char *)dest;
	unsigned char *temps = (unsigned char *)src;

	for(unsigned int i = 0; i < count; i++)
	{
		tempd[i] = temps[i];
	}

	return dest;
}
