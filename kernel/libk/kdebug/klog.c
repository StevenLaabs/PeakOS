#include <drivers/de9.h>

void klog(char* str)
{
	int i = 0;
	while(str[i] != '\0') {
		write_serial(COM1, str[i++]);
	}
}
