#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include <kernel/paging.h>
#include <hal.h>
#include <kernel/terminal.h>
#include <drivers/keyboard.h>
#include <drivers/de9.h>
#include <thirdp/multiboot.h>
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
	printf("Initialized hardware abstraction layer...\n\n");

	multiboot_memory_map_t* map_addr = (multiboot_memory_map_t*)mb_info->mmap_addr;
	multiboot_memory_map_t* map_end = (multiboot_memory_map_t*)(mb_info->mmap_addr + mb_info->mmap_length);

	printf("mmap_addr = 0x%x, mmap_end = 0x%x, mmap_length = 0x%x\n", 
			(unsigned int)map_addr, (unsigned int)map_end, mb_info->mmap_length);

	pmm_init(mb_info);

	while(map_addr != map_end) {
		if(map_addr->type == MULTIBOOT_MEMORY_AVAILABLE)
			pmm_init_region(map_addr->addr, map_addr->len);
		else if(map_addr->type == MULTIBOOT_MEMORY_RESERVED)
			pmm_deinit_region(map_addr->addr, map_addr->len);

		printf(" size = 0x%x, start = 0x%x, size = 0x%x, type = 0x%x\n",
			map_addr->size, (unsigned int)map_addr->addr, (unsigned int)(map_addr->len), map_addr->type);

		map_addr++;
	}

	printf("\npmm regions initialized: %u allocation blocks, free: %u, used or reserved: %u\n\n", 
			(unsigned int)pmm_get_num_blocks(), (unsigned int)pmm_get_num_free(), (unsigned int)pmm_get_num_used());
	
	
	keyboard_init();

	printf("Welcome to PeakOS! - Keyboard input should be enabled\n");
	
	de9_init(COM1);

	while(1) { asm("hlt"); }
}
