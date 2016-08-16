#ifndef _IDT_H
#define _IDT_H

#include <stdint.h>

typedef void (*handler_func_t)(void);

// 8 byte IDT entry
struct idt_entry_t
{
	uint16_t offset1;            // 0-15 bits of the offset
	uint16_t selector;           // code segment select in GDT/LDT
	uint8_t zero;                // these bits are always 0
	uint8_t gate_type       : 4; // See http://wiki.osdev.org/Interrupt_Descriptor_Table#Gate_Types
	uint8_t storage_segment : 1; // 0 for interrupt gate (ISR)
	uint8_t dpl             : 2; // descriptor privilege level
	uint8_t present         : 1; // the entry is present
	uint16_t offset2;            // 16-31 bits of the offset
} __attribute__((packed));

// Pointer to the IDT structure
struct idt_pointer_t
{
	uint16_t limit;
	struct idt_entry_t* base;
} __attribute__((packed));

// info pushed by the interrupt
struct interrupt_data {
	uint32_t ds;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // reverse order pushad pushes the regs in
	uint32_t int_num, error_code;                    // pushed at start of handler
	uint32_t eip, cs, eflags, useresp, ss;
};

/*
 * Sets a gate or entry within the IDT at the given index
 * the isr_adr is the address of the implemented interrupt method
 * see https://www-s.acm.illinois.edu/sigops/2007/roll_your_own/i386/boot.html#predefsel for selector info
 */
void idt_set_gate(uint8_t index, uint32_t isr_adr, uint16_t selector, uint8_t flags);

void idt_install_handler(uint8_t int_num, void (*handler)());

/*
 * Initializes the IDT by setting IDT gaates and loading the IDT pointer into the cpu
 * then mapping the IRQ's to the appropriate locations
 */
void idt_init();

#endif
