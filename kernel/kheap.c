#include <stdio.h>

#include "pmm.h"
#include "paging.h"
#include "kheap.h"

virtual_addr heap_start;
virtual_addr max_heap;
uint8_t kheap_init(virtual_addr start_addr, uint32_t size_in_mb)
{
	uint32_t tables = size_in_mb / 4;

	// allocate the number of page tables needed in a given region
	virtual_addr addr = start_addr;
	for(unsigned int i = 0; i < tables; i++) {
		void* block = pmm_alloc_block();
		if(!block)
			return HEAP_NO_PHYS_MEM;

		if(!paging_map_table(block, (void*)addr))
			return HEAP_INALID_VIRT_MEM;

		// increment by 4MB for page table size
		addr += TABLE_REGION;
	}

	heap_start = start_addr;
	max_heap = addr;

	return 0;
}

void* kmalloc(uint32_t bytes)
{

}

void kfree(void* address)
{
	
}