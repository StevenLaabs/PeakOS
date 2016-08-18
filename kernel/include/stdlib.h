#ifndef _stdlib_h
#define _stdlib_h

int atoi(const char *str);
char* itoa(unsigned int num, char* str, unsigned int base);
char* itoa_signed(int num, char* str, unsigned int base);

void abort(void);

#endif
