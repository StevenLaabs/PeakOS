#include <stdbool.h>
#include <string.h>

#include "pmm.h"

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

static int32_t map_find_free()
{
	for(uint32_t map_byte = 0; map_byte < max_blocks / 32; map_byte++) {
		// check if any bits in these 4 bytes are unset
		if(bitmap[map_byte] != 0xFFFFFFFF) {
			// search for the unset bit
			for(int offset = 0; offset < 32; offset++) {
				int bit = 1 << offset;

				// check if the bit is unset
				if(!(bitmap[map_byte] & bit)) {
					// return the byte position * 4 * 8 + offset
					return (map_byte * 4 * 8 + offset);
				}
			}
		}
	}

	return -1;
}

void pmm_init(multiboot_info_t* mb_info)
{
	extern uint32_t end_kernel_physical;

	bitmap = (uint32_t*)(&end_kernel_physical);
	
	multiboot_memory_map_t* map_addr = (multiboot_memory_map_t*)mb_info->mmap_addr;
	while(map_addr != (multiboot_memory_map_t*)(mb_info->mmap_addr + mb_info->mmap_length)) {
		max_blocks += map_addr->len / BLOCK_SIZE;
		
		if(map_addr->type == MULTIBOOT_MEMORY_RESERVED)
			used_blocks += map_addr->len / BLOCK_SIZE;

		map_addr++;
	}

	used_blocks = max_blocks;

	// set all bits in the bitmap so everything is indicated as used
	memset(bitmap, 0xFF, max_blocks / BLOCKS_PER_BYTE);
}

void pmm_init_region(uint32_t start_addr, size_t size)
{
	int align = start_addr / BLOCK_SIZE;
	int blocks = size / BLOCK_SIZE;

	for(; blocks > 0; blocks--) {
		map_unset(align++);
		used_blocks--;
	}

	map_set(0);
}

void pmm_deinit_region(uint32_t start_addr, size_t size)
{
	int align = start_addr / BLOCK_SIZE;
	int blocks = size / BLOCK_SIZE;

	for(; blocks > 0; blocks--) {
		map_set(align++);
		used_blocks++;
	}
}

void* pmm_alloc_block()
{
	// check for available memory
	if(max_blocks - used_blocks <= 0)
		return 0;

	int32_t block = map_find_free();
	if(block == -1)
		return 0;

	map_set(block);
	
	uint32_t addr = block * BLOCK_SIZE;
	used_blocks++;

	return (void*)addr;
}

void pmm_free_block(void* mem)
{
	uint32_t addr = (uint32_t)mem;
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
