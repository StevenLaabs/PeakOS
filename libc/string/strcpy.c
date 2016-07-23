#include <string.h>

char *strcpy(char *dest, const char *src)
{
	unsigned int i = 0;

	while((dest[i] = src[i]) != '\0')
	{
		i++;
	}

	return dest;
}
