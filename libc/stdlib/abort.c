#include <stdlib.h>
#include <stdio.h>

void abort(void)
{
	printf("Kernel panic: aborting...\n");
	while(1) {}
}
