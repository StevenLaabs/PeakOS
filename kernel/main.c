#include <stddef.h>
#include <stdint.h>

#include "terminal.h"

#define NUM_ENTRIES 1024

extern uint32_t page_table_1[NUM_ENTRIES];
extern uint32_t page_directory[NUM_ENTRIES];

void load_page_dir(uint32_t * directory);
void enable_paging();

void paging_init()
{
	// initialize the page directory
	for(unsigned int i = 0; i < NUM_ENTRIES; i++)
	{
		// Read/Write enabled but page is not present
		page_directory[i] = 0x2;
	}

	// initialize the page_table
	for(unsigned int i = 0; i < NUM_ENTRIES; i++)
	{
		// Read/Write enabled and page present
		page_table_1[i] = (i * 4096) | 3;
	}

	page_directory[0] = ((uint32_t)page_table_1) | 3;

	load_page_dir(page_directory);
	enable_paging();
}

#if defined(__cplusplus)
extern "C"
#endif
void kinit() 
{
	terminal_init();

	terminal_write("Hobby OS has been loaded...");

	paging_init();

	terminal_write(" Paging enabled...");
}
