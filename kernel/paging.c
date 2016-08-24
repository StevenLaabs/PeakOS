#include <stdbool.h>
#include <string.h>

#include "paging.h"
#include "page_dir.h"
#include "page_table.h"
#include "pmm.h"

#define PHYSICAL_BASE_ADDR 0x100000
#define VIRTUAL_BASE_ADDR 0xC0000000
#define KERNEL_PAGE_INDEX (VIRTUAL_BASE_ADDR >> 22)

// get the physical address of a table entry
#define PAGE_PHYSICAL_ADDR(x) (*x & ~0xFFF)

#define PAGE_SIZE 4096

pde_t* current_directory;

void paging_init()
{
	extern pte_t kernel_page_table[1024];
	extern pde_t page_directory[1024];

	// Get physical addresses of the page tables to identity map
	pte_t* physical_page_table = (pte_t*)((pte_t)kernel_page_table - VIRTUAL_BASE_ADDR);
	pde_t* physical_page_directory = (pde_t*)((pde_t)page_directory - VIRTUAL_BASE_ADDR);

	// map the page table to the first 4MB
	for(unsigned int i = 0; i < NUM_ENTRIES; i++) {
		pte_set_address(&physical_page_table[i], i * PAGE_SIZE);
		pte_set_properties(&physical_page_table[i], PRESENT | WRITABLE);
	}

	// Identity map the first 4MB using a 4MB page
	pde_set_address(&physical_page_directory[0], 0x0);
	pde_set_properties(&physical_page_directory[0], PRESENT | WRITABLE | PAGE_MB);

	// Map the virtual kernel address to the physical kernel memory
	pde_set_address(&physical_page_directory[KERNEL_PAGE_INDEX], (uint32_t)physical_page_table);
	pde_set_properties(&physical_page_directory[KERNEL_PAGE_INDEX], PRESENT | WRITABLE);

	// load page directory pointer into cr3 and set enable 4MB pages
	__asm__
	(
		"lea ecx, [page_directory - 0xC0000000]\n"
		"mov cr3, ecx\n"
		"mov ecx, cr4\n"
    	"or ecx, 0x00000010\n"
    	"mov cr4, ecx\n"
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
	);

	// invalidate the 4MB page at start of directory as it is no longer needed
	__asm__
	(
		"mov ecx, 0\n"
		"mov dword [page_directory], ecx\n"
		"invlpg [0]\n"
	);

	current_directory = page_directory;
}

bool page_alloc(pte_t* entry)
{
	void* phys = pmm_alloc_block();

	// check a block was properly allocated
	if(!phys)
		return false;

	// map the entry address and make it present
	pte_set_address(entry, (uint32_t)phys);
	pte_set_properties(entry, PRESENT);

	return true;
}

void page_free(pte_t* entry)
{
	void* phys = (void*)(pte_get_address(*entry));
	
	if(phys)
		pmm_free_block(phys);

	pte_unset_properties(entry, PRESENT);
}

pte_t* page_table_get_entry(pte_t* table, virtual_addr addr)
{
	if(table)
		return &table[PAGE_TABLE_INDEX(addr)];
	
	return 0;
}

pde_t* page_dir_get_entry(pde_t* directory, virtual_addr addr)
{
	if(directory)
		return &directory[PAGE_DIR_INDEX(addr)];

	return 0;
}

pde_t* page_dir_get_current()
{
	return current_directory;
}

void paging_map_page(void* physical, void* virtual)
{
	pde_t* directory = page_dir_get_current();
	pde_t* dir_entry = &directory[PAGE_DIR_INDEX((uint32_t)virtual)];

	// make the page table if it is not present
	if(!pde_test_properties(*dir_entry, PRESENT)) {
		pte_t* table = (pte_t*)pmm_alloc_block();
		if(!table)
			return;

		memset(table, 0, sizeof(pte_t) * NUM_ENTRIES);

		pde_t* entry = &directory[PAGE_DIR_INDEX((uint32_t)virtual)];
		pde_set_address(entry, (uint32_t)virtual);
		pde_set_properties(entry, PRESENT | WRITABLE);
	}

	pte_t* table = (pte_t*)PAGE_PHYSICAL_ADDR((uint32_t*)dir_entry);
	pte_t* table_entry = &table[PAGE_TABLE_INDEX((uint32_t)virtual)];

	pte_set_address(table_entry, (uint32_t)physical);
	pte_set_properties(table_entry, PRESENT);
}

bool paging_switch_directory(pde_t* directory)
{
	if(!directory)
		return false;

	current_directory = directory;
	
	__asm__
	(
		"lea ecx, [current_directory]\n"
		"mov cr3, ecx\n"
	);

	return true;
}

void paging_invalidate_entry(virtual_addr address)
{
	__asm__
	(
		"cli\n"
		"invlpg [%0]\n"
		"sti\n"
		:
		: "r" (address)
	);
}






























