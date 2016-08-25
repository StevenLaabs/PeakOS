#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include <hal.h>
#include <kernel/terminal.h>
#include <drivers/keyboard.h>
#include <drivers/de9.h>
#include <thirdp/multiboot.h>

#include "vga.h"
#include "paging.h"
#include "pmm.h"
#include "kheap.h"

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

	terminal_setcolor(VGA_GREEN, VGA_BLACK);
	printf("Paging enabled, now running in the higher half at 0x%x\n", &start_kernel_virtual);

	hal_init();
	printf("Initialized hardware abstraction layer (GDT, IDT, and PIC configured)\n");

	if(pmm_init(mb_info)) {
		terminal_setcolor(VGA_GREEN, VGA_BLACK);
		printf("Initialized pmm: %u allocation blocks, %u free, %u used or reserved\n", 
			(unsigned)pmm_get_num_blocks(), (unsigned)pmm_get_num_free(), (unsigned)pmm_get_num_used());
	} else {
		terminal_setcolor(VGA_RED, VGA_BLACK);
		printf("Failed to initialize pmm. Check the flags in the multiboot structure\n");
	}

	switch(kheap_init(HEAP_START, HEAP_SIZE)) {
		case 0:
			terminal_setcolor(VGA_GREEN, VGA_BLACK);
			printf("Kernel heap initialized with maximum %uMB starting at 0x%x\n", HEAP_SIZE, HEAP_START);
			break;
		case HEAP_NO_PHYS_MEM:
			terminal_setcolor(VGA_RED, VGA_BLACK);
			printf("Kernel heap failed to initialize: ran out of physical memory\n");
			break;
		case HEAP_INALID_VIRT_MEM:
			terminal_setcolor(VGA_RED, VGA_BLACK);
			printf("Kernel heap failed to initialize: given region is either inaccessible or already reserved\n");
			break;
		default:
			terminal_setcolor(VGA_RED, VGA_BLACK);
			printf("Kernel heap failed to initialize for unknown reasons, check your code!\n");
			break;
	}
	
	keyboard_init();
	terminal_setcolor(VGA_MAGENTA, VGA_BLACK);
	printf("Keyboard driver installed\n");

	de9_init(COM1);
	printf("Serial driver installed for COM1 port\n");

	terminal_setcolor(VGA_WHITE, VGA_BLACK);
	printf("\nWelcome to PeakOS!\n");

	while(1) { asm("hlt"); }
}
