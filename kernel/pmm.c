#include <stdint.h>
#include <stdbool.h>

#include "pmm.h"

#define BLOCKS_PER_BYTE 8
#define BLOCK_SIZE 4096

struct pmm_data {
	uint32_t memory_size;
	uint32_t used_blocks;
	uint32_t max_blocks;
	uint32_t* bitmap;
};
typedef pmm_data pmm_data_t;

static pmm_data_t pmm = { 0, 0, 0, 0 };

// Sets a specific bit contained within the bitmap
inline void map_set(uint32_t bit)
{
	pmm.bitmap[bit / 32] |= (1 << (bit % 32));
}

// Unsets a specific bit contained within the bitmap
inline void map_unset(uint32_t bit)
{
	pmm.bitmap[bit / 32] &= ~(1 << (bit % 32));
}

// Returns true if a bit is set and false if a bit is unset
inline bool map_check(uint32_t bit)
{
	return pmm.bitmap[bit / 32] & (1 << (bit % 32));
}

uint32_t map_find_free()
{
	for(uint32_t map_byte = 0; map_byte < pmm.max_blocks / 32; map_byte++) {
		// check if any bits in these 4 bytes are unset
		if(pmm.bitmap[map_byte] != 0xFFFFFFFF) {
			// search for the unset bit
			for(int offset = 0; offset < 32; offset++) {
				int bit = 1 << offset;

				// check if the bit is unset
				if(!pmm.bitmap[map_byte] & bit) {
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
	
}
