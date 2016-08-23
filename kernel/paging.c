#include <stdbool.h>
#include <string.h>
#include <kernel/paging.h>
#include "pmm.h"

typedef uint32_t virtual_addr;

#define NUM_ENTRIES 1024
#define NUM_TABLES 1024
#define VIRTUAL_BASE_ADDR 0xC0000000
#define KERNEL_PAGE_INDEX (VIRTUAL_BASE_ADDR >> 22)

#define PAGE_SIZE 4096

#define READ 0
#define WRITE 1
#define SUPERVISOR 0
#define USER 1
#define WRITE_BACK 0
#define WRITE_THROUGH 1

#define PAGE_DIR_INDEX(i) (((i) >> 22) & 0x3FF)
#define PAGE_TABLE_INDEX(i) (((i) >> 12) & 0x3FF)
#define PAGE_PHYSICAL_ADDR(a) (*a & ~0xFFF)

struct pte {
	uint32_t present : 1;
	uint32_t writable : 1;
	uint32_t mode : 1;
	uint32_t reserved_intel : 2;
	uint32_t accessed : 1;
	uint32_t dirty : 1;
	uint32_t reserved : 2;

	uint32_t available : 3;

	uint32_t address : 20;
} __attribute__((packed));
typedef struct pte pte_t;

struct pde {
	uint32_t present : 1;
	uint32_t writable : 1;
	uint32_t mode : 1;
	uint32_t write_through : 1;
	uint32_t cache_enabled : 1;
	uint32_t accessed : 1;
	uint32_t reserved : 1;
	uint32_t size : 1;
	uint32_t global : 1;

	uint32_t available : 3;

	uint32_t address: 20;
} __attribute__((packed));
typedef struct pde pde_t;

struct page_table {
	pte_t entries[NUM_ENTRIES];
};
typedef struct page_table page_table_t;

struct page_directory {
	pde_t entries[NUM_TABLES];
};
typedef struct page_directory page_directory_t;

extern uint32_t page_tables[NUM_ENTRIES * NUM_TABLES];
extern uint32_t page_directory[NUM_ENTRIES];

page_directory_t* current_directory;

inline bool paging_switch_directory(page_directory_t* directory)
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

bool page_alloc(pte_t* entry)
{
	void* phys = pmm_alloc_block();

	// check a block was properly allocated
	if(!phys)
		return false;

	// map the entry address and make it present
	entry->address = ((uint32_t)phys) >> 12;
	entry->present = 0x1;

	return true;
}

void page_free(pte_t* entry)
{
	void* phys = (void*)(entry->address << 12);
	
	if(phys)
		pmm_free_block(phys);

	entry->present = 0x0;
}

pte_t* page_table_get_entry(page_table_t* pt, virtual_addr addr)
{
	if(pt)
		return &pt->entries[PAGE_TABLE_INDEX(addr)];
	
	return 0;
}

pde_t* page_dir_get_entry(page_directory_t* pd, virtual_addr addr)
{
	if(pd)
		return &pd->entries[PAGE_DIR_INDEX(addr)];

	return 0;
}

page_directory_t* page_dir_get_current()
{
	return current_directory;
}

/*void paging_invalidate_entry(virtual_addr addr)
{
	__asm__
	(
		"cli\n"
		"invlpg addr\n"
		"sti\n"
	);
}*/

void paging_map_page(void* physical, void* virtual)
{
	page_directory_t* directory = page_dir_get_current();
	pde_t* dir_entry = &directory->entries[PAGE_DIR_INDEX((uint32_t)virtual)];

	// make the page table if it is not present
	if(!dir_entry->present) {
		page_table_t* table = (page_table_t*) pmm_alloc_block();
		if(!table)
			return;

		memset(table, 0, sizeof(page_table_t));

		pde_t* entry = &directory->entries[PAGE_DIR_INDEX((uint32_t)virtual)];
		entry->present = 0x1;
		entry->writable = WRITE;
		entry->address = ((virtual_addr)virtual) >> 12;
	}

	page_table_t* table = (page_table_t*)PAGE_PHYSICAL_ADDR((uint32_t*)dir_entry);
	pte_t* table_entry = &table->entries[PAGE_TABLE_INDEX((uint32_t)virtual)];

	table_entry->address = ((uint32_t)physical) >> 12;
	table_entry->present = 0x1;
}
































