#include <stddef.h>
#include <stdint.h>

#include "terminal.h"
#include "paging.h"

#if defined(__cplusplus)
extern "C"
#endif
void kinit() 
{
	paging_init();

	terminal_init();

	terminal_write("Hobby OS has been loaded...\n");

	terminal_write("Paging enabled with higher half...");
}
