#include <stdbool.h>
#include <string.h>

#include "pmm.h"

#define VIRTUAL_BASE_ADDR 0xC0000000
#define BLOCKS_PER_BYTE 8
#define BLOCK_SIZE 4096

static uint32_t used_blocks = 0;
static uint32_t max_blocks = 0;
static uint32_t* bitmap;

// Sets a specific bit contained within the bitmap
inline static void map_set(uint32_t bit)
{
	bitmap[bit / 32] |= (1 << (bit % 32));
}

// Unsets a specific bit contained within the bitmap
inline static void map_unset(uint32_t bit)
{
	bitmap[bit / 32] &= ~(1 << (bit % 32));
}

// Returns true if a bit is set and false if a bit is unset
inline static bool map_check(uint32_t bit)
{
	return bitmap[bit / 32] & (1 << (bit % 32));
}

static uint32_t map_find_free()
{
	for(uint32_t map_byte = 0; map_byte < max_blocks / 32; map_byte++) {
		// check if any bits in these 4 bytes are unset
		if(bitmap[map_byte] != 0xFFFFFFFF) {
			// search for the unset bit
			for(unsigned int offset = 0; offset < 32; offset++) {
				unsigned int bit = 1 << offset;

				// check if the bit is unset
				if(!(bitmap[map_byte] & bit)) {
					// return the byte position * 4 * 8 + offset
					return (map_byte * 4 * 8 + offset);
				}
			}
		}
	}

	return 0;
}

uint8_t pmm_init(multiboot_info_t* mb_info)
{
	if(!(mb_info->flags & (1 << 6)))
		return 0;

	extern uint32_t start_kernel_physical;
	extern uint32_t end_kernel_physical;
	extern uint32_t end_kernel_virtual;

	bitmap = (uint32_t*)(&end_kernel_virtual);
	
	multiboot_memory_map_t* map_addr = (multiboot_memory_map_t*)mb_info->mmap_addr;
	while(map_addr != (multiboot_memory_map_t*)(mb_info->mmap_addr + mb_info->mmap_length)) {
		max_blocks += map_addr->len / BLOCK_SIZE;

		map_addr++;
	}

	// set all bits in the bitmap so everything is indicated as used
	memset(bitmap, 0xFF, max_blocks / BLOCKS_PER_BYTE);
	used_blocks = max_blocks;
	
	// reserve and free blocks according to the mmap from multiboot
	// keep the first 1MB marked as reserved to preserve things such as
	// the multiboot structures
	map_addr = (multiboot_memory_map_t*)mb_info->mmap_addr;
	while(map_addr != (multiboot_memory_map_t*)(mb_info->mmap_addr + mb_info->mmap_length)) {
		if(map_addr->addr >= 0x100000 && map_addr->type == MULTIBOOT_MEMORY_AVAILABLE) {
			pmm_init_region(map_addr->addr, map_addr->len);	
		}

		map_addr++;
	}

	// make sure the kernel memory is reserved
	pmm_deinit_region((uint32_t)&start_kernel_physical, (size_t)((uint32_t)&end_kernel_physical - (uint32_t)&start_kernel_physical));

	// reserve the memory space taken up by the bitmap
	pmm_deinit_region(((uint32_t)bitmap) - VIRTUAL_BASE_ADDR, ((size_t)((uint32_t)&bitmap[max_blocks / 32] - (uint32_t)bitmap)));

	return 1;
}

void pmm_init_region(uint32_t start_addr, size_t size)
{
	uint32_t align = ALIGN_UP(start_addr);
	uint32_t blocks = ALIGN_UP(size) / BLOCK_SIZE;

	if(blocks == 0)
		blocks = 1;

	for(; blocks > 0; blocks--) {
		map_unset(align / BLOCK_SIZE);

		align += 4096;
		used_blocks--;
	}

	map_set(0);
}

void pmm_deinit_region(uint32_t start_addr, size_t size)
{
	uint32_t align = ALIGN_UP(start_addr);
	uint32_t blocks = ALIGN_UP(size) / BLOCK_SIZE;

	if(blocks == 0)
		blocks = 1;

	for(; blocks > 0; blocks--) {
		map_set(align / BLOCK_SIZE);

		align += 4096;
		used_blocks++;
	}
}

void* pmm_alloc_block()
{
	// check for available memory
	if(max_blocks - used_blocks <= 0)
		return 0;

	uint32_t block = map_find_free();
	if(!block)
		return 0;

	map_set(block);
	
	uint32_t addr = block * BLOCK_SIZE;
	used_blocks++;

	return (void*)addr;
}

void pmm_free_block(void* mem)
{
	uint32_t addr = ALIGN_DOWN((uint32_t)mem);
	uint32_t block = addr / BLOCK_SIZE;

	map_unset(block);

	used_blocks--;
}

uint32_t pmm_get_num_blocks()
{
	return max_blocks;
}

uint32_t pmm_get_num_free()
{
	return max_blocks - used_blocks;
}

uint32_t pmm_get_num_used()
{
	return used_blocks;
}
