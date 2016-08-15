#include <stdlib.h>
#include <stdbool.h>

char* itoa(int num, char* str, int base)
{
	bool is_negative = false;

	if(num < 0 && base == 10) {
		num = -num;
		is_negative = true;
	}

	int start_num = num;
	static char buf[32] = {0};

	int i = 30;

	for(; num && i; --i, num /= base)
		buf[i] = "0123456789ABCDEF"[num % base];

	int str_ind = 0;

	if(base == 16) {
		str[str_ind++] = '0';
		str[str_ind++] = 'x';
	} else if(base == 2) {
		str[str_ind++] = '0';
		str[str_ind++] = 'b';
	} else if(is_negative) {
		str[str_ind++] = '-';
	}

	if(start_num == 0)
		str[str_ind++] = '0';
	else {
		while(buf[++i] != '\0') {
			str[str_ind++] = buf[i];
		}
	}

	return str;
}
