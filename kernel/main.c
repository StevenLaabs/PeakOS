#include <stddef.h>
#include <stdint.h>

#include "terminal.h"

#define NUM_ENTRIES 1024
#define VIRTUAL_BASE_ADDR 0xC0000000
#define PAGE_DIR_INDEX (VIRTUAL_BASE_ADDR >> 22)

extern uint32_t page_table_1[NUM_ENTRIES];
extern uint32_t page_directory[NUM_ENTRIES];

void load_page_dir(uint32_t * directory);
void enable_paging();
void start_in_higher_half();

void paging_init()
{
	// Get physical addresses of the page tables to identity map
	uint32_t * physical_page_table_1 = (uint32_t *)((uint32_t) page_table_1 - VIRTUAL_BASE_ADDR);
	uint32_t * physical_page_directory = (uint32_t *)((uint32_t) page_directory - VIRTUAL_BASE_ADDR);

	// initialize page directory for empty entries
	for(unsigned int i = 0; i < NUM_ENTRIES; i++)
	{
		physical_page_directory[i] = 0x2;
	}

	// initialize the page table with read/write and present bits
	for(unsigned int i = 0; i < NUM_ENTRIES; i++)
	{
		physical_page_table_1[i] = (i * 4096) | 3;
	}

	uint32_t start_entry_index = PAGE_DIR_INDEX * 1024;
	for(unsigned int i = 0; i < (NUM_ENTRIES + start_entry_index); i++)
	{
		physical_page_table_1[i] = (i * 4096) | 3;
	}

	// set the first entry in the directory to the page table
	physical_page_directory[0] = ((uint32_t)physical_page_table_1) | 3;

	// initialize the page directory
	//for(unsigned int i = 0; i < NUM_ENTRIES; i++)
	//{
	//	// Read/Write enabled but page is not present
	//	page_directory[i] = 0x2;
	//}

	// initialize the page_table
	//for(unsigned int i = 0; i < NUM_ENTRIES; i++)
	//{
	//	// Read/Write enabled and page present
	//	page_table_1[i] = (i * 4096) | 3;
	//}

	//page_directory[0] = ((uint32_t)page_table_1) | 3;

	load_page_dir(page_directory);
	enable_paging();
	
	__asm__
	(
		"lea higher_half, %ecx\n"
		"jmp *%ecx\n"
		"higher_half:\n"
		"nop\n"
	);
}

#if defined(__cplusplus)
extern "C"
#endif
void kinit() 
{
	terminal_init();

	terminal_write("Hobby OS has been loaded...");

	//paging_init();

	//terminal_write(" Paging enabled...");
}
