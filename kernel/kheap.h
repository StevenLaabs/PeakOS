#ifndef _KHEAP_H
#define _KHEAP_H

#define HEAP_NO_PHYS_MEM 1
#define HEAP_INALID_VIRT_MEM 2

#define HEAP_START 0xF0000000
#define HEAP_SIZE 64

uint8_t kheap_init(virtual_addr start_addr, uint32_t size_in_mb);
void* kmalloc(uint32_t bytes);
void kfree(void* address);

#endif