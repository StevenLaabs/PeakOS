#ifndef _IDT_H
#define _IDT_H

#include <stdint.h>

#define PIT_CH0_PORT 0x40
#define PIT_CH1_PORT 0x41
#define PIT_CH2_PORT 0x42
#define PIT_CMD_PORT 0x43

// 8 byte IDT entry
struct idt_entry_t
{
	uint16_t offset1;  // 0-15 bits of the offset
	uint16_t selector; // code segment select in GDT/LDT
	uint8_t zero;      // these bits are always 0
	uint8_t gate_type       : 4; // See http://wiki.osdev.org/Interrupt_Descriptor_Table#Gate_Types
	uint8_t storage_segment : 1; // 0 for interrupt gate (ISR)
	uint8_t dpl             : 2; // descriptor privilege level
	uint8_t present         : 1; // the entry is present
	uint16_t offset2;  // 16-31 bits of the offset
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

struct idt_entry_t* idt; // 256 interrupt entries in the IDT
struct idt_pointer_t* idt_ptr;   // pointer info for the IDT

// Sets a gate or entry within the IDT at the given index
// the isr_adr is the address of the implemented interrupt method
// see https://www-s.acm.illinois.edu/sigops/2007/roll_your_own/i386/boot.html#predefsel for selector info
void idt_set_gate(uint8_t index, uint32_t isr_adr, uint16_t selector, uint8_t flags);

void idt_init();

#endif
