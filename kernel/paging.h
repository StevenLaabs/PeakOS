#ifndef _paging_h
#define _paging_h

#include <stdint.h>

#define NUM_ENTRIES 1024
#define NUM_TABLES 1024
#define VIRTUAL_BASE_ADDR 0xC0000000
#define KERNEL_PAGE_INDEX (VIRTUAL_BASE_ADDR >> 22)

extern uint32_t page_tables[NUM_ENTRIES * NUM_TABLES];
extern uint32_t page_directory[NUM_ENTRIES];

void paging_init();

#endif
