#include <stdlib.h>
#include <stdbool.h>

char* itoa(unsigned int num, char* str, unsigned int base)
{
	int pos = 0;
	int opos = 0;
	int top = 0;

	char temp[32];
	char* digits = "0123456789ABCDEF";

	// invalid base or 0 value
	if(num == 0 || base > 16) {
		str[0] = '0';
		str[1] = '\0';
		return str;
	}

	while(num != 0) {
		temp[pos] = digits[num % base];
		pos++;
		num /= base;
	}

	top = pos--;
	for(opos = 0; opos < top; pos--, opos++) {
		str[opos] = temp[pos];
	}

	str[opos] = 0;

	return str;
}

char* itoa_signed(int num, char* str, unsigned int base)
{
	if(num < 0) {
		*str++ = '-';
		num *= -1;
	}

	itoa(num, str, base);

	return --str;
}
