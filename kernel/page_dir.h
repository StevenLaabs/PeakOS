#ifndef _PAGE_DIR_H
#define _PAGE_DIR_H

#include <stdint.h>
#include <stdbool.h>

#define NUM_TABLES 1024

// Flag bits
#define PRESENT 0x1
#define WRITABLE 0x2
#define USER_MODE 0x4
#define WRITE_THROUGH 0x8
#define CACHE 0x10
#define PAGE_MB 0x80

// Section bits
#define PROPERTIES 0xFFF
#define ADDRESS 0x7FFFF000

// Converts a virtual address to a page directory index
#define PAGE_DIR_INDEX(i) (((i) >> 22) & 0x3FF)

typedef uint32_t pde_t;

// Set each of the given properties bits in the given entry
static void pde_set_properties(pde_t* pde, uint32_t properties)
{
	*pde = (*pde) | properties;
}

// Unset all of the given property bits in the given entry
static void pde_unset_properties(pde_t* pde, uint32_t properties)
{
	*pde = (*pde) & ~(properties);
}

// Return true if all of the properties in the entry are set, false otherwise
static bool pde_test_properties(pde_t pde, uint32_t properties)
{
	return (pde & properties) == properties;
}

// Set the given entry's address bits to the given address
static void pde_set_address(pde_t* pde, uint32_t address)
{
	*pde = ((*pde) & PROPERTIES) | address;
}

// Return the physical address contained within the entry
static uint32_t pde_get_address(pde_t pde)
{
	return (pde & ADDRESS);
}

#endif