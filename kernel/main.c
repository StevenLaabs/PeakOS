#include <stddef.h>
#include <stdint.h>

#include "terminal.h"
#include "paging.h"
#include "idt.h"

void issue_interrupt(unsigned char i)
{
	switch(i)
	{
		case 0: __asm__("int 0\n"); break;
		case 1: __asm__("int 1\n"); break;
		case 2: __asm__("int 2\n"); break;
		case 3: __asm__("int 3\n"); break;
		case 4: __asm__("int 4\n"); break;
		case 5: __asm__("int 5\n"); break;
		case 6: __asm__("int 6\n"); break;
		case 7: __asm__("int 7\n"); break;
		case 8: __asm__("int 8\n"); break;
		case 9: __asm__("int 9\n"); break;
		case 10: __asm__("int 10\n"); break;
		case 11: __asm__("int 11\n"); break;
		case 12: __asm__("int 12\n"); break;
		case 13: __asm__("int 13\n"); break;
		case 14: __asm__("int 14\n"); break;
		case 15: __asm__("int 15\n"); break;
		case 16: __asm__("int 16\n"); break;
		case 17: __asm__("int 17\n"); break;
		case 18: __asm__("int 18\n"); break;
		case 19: __asm__("int 19\n"); break;
		case 20: __asm__("int 20\n"); break;
		case 32: __asm__("int 32\n"); break;
		case 33: __asm__("int 33\n"); break;
		case 34: __asm__("int 34\n"); break;
		case 35: __asm__("int 35\n"); break;
		case 36: __asm__("int 36\n"); break;
		case 37: __asm__("int 37\n"); break;
		case 38: __asm__("int 38\n"); break;
		case 39: __asm__("int 39\n"); break;
		case 40: __asm__("int 40\n"); break;
		case 41: __asm__("int 41\n"); break;
		case 42: __asm__("int 42\n"); break; 
		case 43: __asm__("int 43\n"); break;
		case 44: __asm__("int 44\n"); break;
		case 45: __asm__("int 45\n"); break;
		case 46: __asm__("int 46\n"); break;
		case 47: __asm__("int 47\n"); break;
		default: terminal_write("Invalid interrupt number\n"); break;
	}
}

#if defined(__cplusplus)
extern "C"
#endif
void kinit() 
{
	paging_init();

	terminal_init();

	terminal_write("Hobby OS has been loaded...\n");

	terminal_write("Paging enabled with higher half...\n");

	idt_init();

	terminal_write("IDT initialized...\n");
	terminal_write("Testing interrupt handlers...\n");

	//unsigned int i = 0x400000;
	//while(i-- > 0) {}

	//for(unsigned char i = 0; i < 21; i++)
	//{
	//	issue_interrupt(i);
	//}
}
