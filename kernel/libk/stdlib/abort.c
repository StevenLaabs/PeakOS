#include <stdlib.h>
#include <stdio.h>

void abort(void)
{
	asm("cli");
	printf("Kernel panic! Aborting...\n");
	while(1) {}
}
