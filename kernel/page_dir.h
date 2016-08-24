#include <stdint.h>

#define NUM_TABLES 1024

#define PRESENT 0x1
#define WRITABLE 0x2
#define USER_MODE 0x4
#define WRITE_THROUGH 0x8
#define CACHE 0x10
#define PAGE_MB 0x80

#define PROPERTIES 0xFFF
#define ADDRESS 0x7FFFF000

#define PAGE_DIR_INDEX(i) (((i) >> 22) & 0x3FF)

typedef uint32_t pde_t;

static void pde_set_properties(pde_t* pde, uint32_t properties)
{
	*pde = (*pde) | properties;
}

static void pde_unset_properties(pde_t* pde, uint32_t properties)
{
	*pde = (*pde) & ~(properties);
}

static uint32_t pde_test_properties(pde_t pde, uint32_t properties)
{
	return (pde & properties);
}

static void pde_set_address(pde_t* pde, uint32_t address)
{
	*pde = ((*pde) & PROPERTIES) | address;
}

static uint32_t pde_get_address(pde_t pde)
{
	return (pde & ADDRESS);
}