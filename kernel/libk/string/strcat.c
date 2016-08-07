#include <string.h>

char *strcat(char *dest, const char *src)
{
	size_t dest_pos;
	size_t src_pos;

	for(dest_pos = 0; dest[dest_pos] != '\0'; dest_pos++) {}

	for(src_pos = 0; src[src_pos] != '\0'; src_pos++)
	{
		dest[dest_pos + src_pos] = src[src_pos];
	}

	dest[dest_pos + src_pos] = '\0';

	return dest;
}
