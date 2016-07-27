#include "idt.h"

static void idt_set_gate(uint8_t index, uint32_t isr_adr, uint16_t selector, uint8_t flags)
{
	idt[index].offset1 = (isr_adr & 0xFFFF);
	idt[index].offset2 = ((isr_adr >> 16) & 0xFFFF);
	idt[index].selector = selector;
	idt[index].flags = flags;
	idt[index].zero = 0;
}

void idt_init()
{
	idtp.base = (uint32_t)&idt;
	idtp.limit = (sizeof(struct idt_entry) * 256) - 1;

	

	__asm__
	(
		"mov eax, [idtp]\n"
		"lidt [eax]"
	);
}
