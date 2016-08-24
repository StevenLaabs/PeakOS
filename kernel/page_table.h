#ifndef _PAGE_TABLE_H
#define _PAGE_TABLE_H

#include <stdint.h>
#include <stdbool.h>

#define NUM_ENTRIES 1024

// Flag bits
#define PRESENT 0x1
#define WRITABLE 0x2
#define USER_MODE 0x4

// Section bits
#define PROPERTIES 0xFFF
#define ADDRESS 0x7FFFF000

// Converts a virtual address to a page table index
#define PAGE_TABLE_INDEX(i) (((i) >> 12) & 0x3FF)

typedef uint32_t pte_t;

// Set each of the given properties bits in the given entry
static void pte_set_properties(pte_t* pte, uint32_t properties)
{
	*pte = (*pte) | properties;
}

// Unset all of the given property bits in the given entry
static void pte_unset_properties(pte_t* pte, uint32_t properties)
{
	*pte = (*pte) & ~(properties);
}

// Return true if all of the properties in the entry are set, false otherwise
static bool pte_test_properties(pte_t pte, uint32_t properties)
{
	return (pte & properties) == properties;
}

// Set the given entry's address bits to the given address
static void pte_set_address(pte_t* pte, uint32_t address)
{
	*pte = ((*pte) & PROPERTIES) | address;
}

// Return the physical address contained within the entry
static uint32_t pte_get_address(pte_t pte)
{
	return (pte & ADDRESS);
}

#endif