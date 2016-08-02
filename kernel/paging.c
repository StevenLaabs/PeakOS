#include <kernel/paging.h>

void paging_init()
{
	// Get physical addresses of the page tables to identity map
	uint32_t * physical_page_table_1 = (uint32_t *)((uint32_t) page_tables - VIRTUAL_BASE_ADDR);
	uint32_t * physical_page_directory = (uint32_t *)((uint32_t) page_directory - VIRTUAL_BASE_ADDR);

	uint32_t flags = 3;
	uint32_t num_page_tables = 4;
	uint32_t size_of_tables = num_page_tables * NUM_ENTRIES;

	// initialize page table entries
	for(unsigned int i = 0; i < size_of_tables; i++) {
		physical_page_table_1[i] = (i * 4096) | flags;
	}

	// identity map the kernel addresses in the page table
	uint32_t start_entry_index = (KERNEL_PAGE_INDEX * 1024);
	for(unsigned int i = 0; i < size_of_tables; i++) {
		physical_page_table_1[i + start_entry_index] = (i * 4096) | flags;
	}

	// map the page directory to the tables
	start_entry_index = (uint32_t)physical_page_table_1;
	for(unsigned int i = 0; i < NUM_ENTRIES; i++) {
		physical_page_directory[i] = (start_entry_index + (i * 4096)) | flags;
	}

	// load page directory pointer into cr3
	__asm__
	(
		"lea ecx, [page_directory - 0xC0000000]\n"
		"mov cr3, ecx\n"
	);

	// initialize paging by setting bit 31 in cr0
	__asm__
	(
		"mov ecx, cr0\n"
		"or ecx, 0x80000000\n"
		"mov cr0, ecx\n"
	);

	// long jump to the higher half address for the kernel
	__asm__
	(
		"lea ecx, [higher_half]\n"
		"jmp ecx\n"
		"higher_half:\n"
		"nop\n"
	);
}
