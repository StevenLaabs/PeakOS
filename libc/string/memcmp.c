#include <string.h>

int memcmp(const void *lhs, const void *rhs, size_t count)
{
	const unsigned char * ptr1 = (const unsigned char *)lhs;
	const unsigned char * ptr2 = (const unsigned char *)rhs;

	for(unsigned int i = 0; i < count; i++)
	{
		if(ptr1[i] < ptr2[i])
			return -1;

		if(ptr1[i] > ptr2[i])
			return 1;
	}

	return 0;
}
