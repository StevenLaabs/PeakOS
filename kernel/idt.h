#include <stdint.h>

// Pointer to the IDT structure 
struct idt_pointer
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

// 8 byte IDT entry
struct idt_entry
{
	uint16_t offset1;  // 0-15 bits of the offset
	uint16_t selector; // code segment select in GDT/LDT
	uint8_t zero;      // these bits are always 0
	uint8_t flags;     // types/attributes of the entry
	uint16_t offset2;  // 16-31 bits of the offset
} __attribute__((packed));

struct idt_entry idt[256]; // 256 interrupt entries in the IDT
struct idt_pointer idtp;   // pointer info for the IDT

// Sets a gate or entry within the IDT at the given index
// the isr_adr is the address of the implemented interrupt method
// see https://www-s.acm.illinois.edu/sigops/2007/roll_your_own/i386/boot.html#predefsel for selector info
static void idt_set_gate(uint8_t index, uint32_t isr_adr, uint16_t selector, uint8_t flags);

void idt_init();
