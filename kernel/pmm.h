#ifndef _PMM_H
#define _PMM_H

#include <stdint.h>
#include <stddef.h>
#include <thirdp/multiboot.h>

#define ALIGN_UP(x) (((x) + (4096) - 1) & (~((4096) - 1)))
#define ALIGN_DOWN(x) ((x) & ~((4096) - 1))

/*
 * Initializes the pmm using the multiboot info structure to check
 * the memory map flags are set then using the multiboot mmap to mark
 * reserved regions and calculate the available 4KB blocks of memory
 */
uint8_t pmm_init(multiboot_info_t* mb_info);

/*
 * Initializes a region of memory from the start address for
 * the length of the given size by marking the corresponding
 * parts of the bitmap as unused
 */
void pmm_init_region(uint32_t start_addr, size_t size);

/*
 * Deinitializes a region of memory from the start address
 * for the length of the given size by marking the
 * corresponding parts of the bitmap as used
 */
void pmm_deinit_region(uint32_t start_addr, size_t size);

/*
 * Allocates a 4KB block of physical memory by finding a free
 * space, marking it as used, and returning a pointer to the address
 */
void* pmm_alloc_block();

/*
 * Deallocates the given physical memory address by finding the
 * corresponding position in the bitmap and marking it as unused
 */
void pmm_free_block(void* mem);

// Return the total number of 4KB blocks available in physical memory
uint32_t pmm_get_num_blocks();

// Return number of unallocated blocks of physical memory available
uint32_t pmm_get_num_free();

// Return number of free or reserved blocks of physical memory
uint32_t pmm_get_num_used();

#endif
