#ifndef _string_h
#define _string_h

#include <stddef.h>

char *strcpy(char *dest, const char *src);
char *strcat(char *dest, const char *src);

size_t strlen(const char *str);

int strcmp(const char *lhs, const char *rhs);

void *memset(void *dest, int ch, size_t count);
void *memcpy(void *dest, const void *src, size_t count);
void *memmove(void *dest, const void *src, size_t count);
int memcmp(const void *lhs, const void *rhs, size_t count);
void *memchr(const void *str, int ch, size_t count);

#endif
