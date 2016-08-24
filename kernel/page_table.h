#include <stdint.h>

#define NUM_ENTRIES 1024

#define PRESENT 0x1
#define WRITABLE 0x2
#define USER_MODE 0x4

#define PROPERTIES 0xFFF
#define ADDRESS 0x7FFFF000

#define PAGE_TABLE_INDEX(i) (((i) >> 12) & 0x3FF)

typedef uint32_t pte_t;

static void pte_set_properties(pte_t* pte, uint32_t properties)
{
	*pte = (*pte) | properties;
}

static void pte_unset_properties(pte_t* pte, uint32_t properties)
{
	*pte = (*pte) & ~(properties);
}

static uint32_t pte_test_properties(pte_t pte, uint32_t properties)
{
	return (pte & properties);
}

static void pte_set_address(pte_t* pte, uint32_t address)
{
	*pte = ((*pte) & PROPERTIES) | address;
}

static uint32_t pte_get_address(pte_t pte)
{
	return (pte & ADDRESS);
}