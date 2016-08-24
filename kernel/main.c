#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include <hal.h>
#include <kernel/terminal.h>
#include <drivers/keyboard.h>
#include <drivers/de9.h>
#include <thirdp/multiboot.h>

#include "paging.h"
#include "pmm.h"

void issue_interrupt(unsigned char i)
{
	switch(i) {
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
		default: printf("Invalid interrupt number: %i\n", i); break;
	}
}


extern uint32_t start_kernel_physical;
extern uint32_t end_kernel_physical;
extern uint32_t start_kernel_virtual;
extern uint32_t end_kernel_virtual;

#if defined(__cplusplus)
extern "C"
#endif
void kinit(multiboot_info_t* mb_info)
{
	paging_init();

	terminal_init();

	printf("Paging enabled with higher half...\n");

	hal_init();
	printf("Initialized hardware abstraction layer...\n");

	if(pmm_init(mb_info)) {
		printf("Initialized pmm: %u allocation blocks, %u free, %u used or reserved\n\n", 
			(unsigned)pmm_get_num_blocks(), (unsigned)pmm_get_num_free(), (unsigned)pmm_get_num_used());
	} else {
		printf("Failed to initialize pmm. Check the flags in the multiboot structure");
	}

	
	void* p = pmm_alloc_block();
	if(p)
		printf("p allocated at 0x%x\n", (unsigned)p);

	void* q = pmm_alloc_block();
	if(q)
		printf("q allocated at 0x%x\n", (unsigned)q);
	
	pmm_free_block(p);
	printf("Deallocated p\n");

	p = pmm_alloc_block();
	if(p)
		printf("p reallocated at 0x%x\n", (unsigned)p);

	void *r = pmm_alloc_block();
	if(r)
		printf("r allocated at 0x%x\n\n", (unsigned)r);
	
	keyboard_init();

	printf("Welcome to PeakOS! - Keyboard input should be enabled\n");
	
	de9_init(COM1);

	while(1) { asm("hlt"); }
}
