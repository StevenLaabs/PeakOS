#include <stddef.h>
#include <stdint.h>

#if defined(__cplusplus)
extern "C"
#endif
void kmain() 
{
	uint16_t* vga = (uint16_t*) 0xB8000;
	
	vga[0] = 0x4f524f45;
}
