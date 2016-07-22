#include <stddef.h>
#include <stdint.h>

#include "terminal.h"

#if defined(__cplusplus)
extern "C"
#endif
void kinit() 
{
	terminal_init();

	terminal_write("Hobby OS has been loaded.");
}
