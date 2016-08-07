#include <string.h>

void *memmove(void *dest, const void *src, size_t count)
{
	unsigned char * ptrd = (unsigned char *)dest;
	const unsigned char * ptrs = (const unsigned char *)src;

	if(ptrd < ptrs)
	{
		for(unsigned int i = 0; i < count; i++)
		{
			ptrd[i] = ptrs[i];
		}
	}

	else
	{
		for(unsigned int i = count; i != 0; i--)
		{
			ptrd[i - 1] = ptrs[i - 1];
		}
	}

	return dest;
}
