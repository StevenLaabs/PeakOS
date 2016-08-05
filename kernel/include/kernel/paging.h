#ifndef _PAGING_H
#define _PAGING_H

#include <stdint.h>

/*
 * Configures initial page tables and page directory by identity mapping
 * the kernel addresses in the page table and loading the directory into the cr3 register
 * then performing a long jump to the higher half address
 */
void paging_init();

#endif
