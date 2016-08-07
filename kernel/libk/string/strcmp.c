#include <string.h>

int strcmp(const char *lhs, const char *rhs)
{
	const char * str1 = lhs;
	const char * str2 = rhs;

	while(*str1 != '\0')
	{
		if(*str2 == '\0')
			return 1;

		if(*str1 < *str2)
			return -1;

		if(*str1 > *str2)
			return 1;

		str1++;
		str2++;
	}

	if(*str2 != '\0')
		return -1;

	return 0;
}
