#ifndef _PMM_H
#define _PMM_H

#include <stdint.h>
#include <thirdp/multiboot.h>

void pmm_init(multiboot_info_t* mb_info);

void pmm_init_region(uint32_t start_addr, size_t size);

void pmm_deinit_region(uint32_t start_addr, size_t size);

void* pmm_alloc_block();

void pmm_free_block(void* mem);

uint32_t pmm_get_num_blocks();
uint32_t pmm_get_num_free();
uint32_t pmm_get_num_used();

#endif
