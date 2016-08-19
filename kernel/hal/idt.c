#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <hal.h>
#include <drivers/keyboard.h>

#include "idt.h"

// macro defines a function for the interrupt handler number
#define NEW_INTERRUPT_HANDLER(i) extern void interrupt_handler_##i(void)

#define IDT_SET_GATE(index) idt_set_gate(index, (uint32_t)&interrupt_handler_##index, 0x08, 0x8E);

static struct idt_entry_t* idt; // 256 interrupt entries in the IDT
static struct idt_pointer_t* idt_ptr;   // pointer info for the IDT

extern uint32_t idt_pointer;
extern uint32_t idt_contents;

// Exception interrupts go 0-20: http://wiki.osdev.org/Exceptions
NEW_INTERRUPT_HANDLER(0);
NEW_INTERRUPT_HANDLER(1);
NEW_INTERRUPT_HANDLER(2);
NEW_INTERRUPT_HANDLER(3);
NEW_INTERRUPT_HANDLER(4);
NEW_INTERRUPT_HANDLER(5);
NEW_INTERRUPT_HANDLER(6);
NEW_INTERRUPT_HANDLER(7);
NEW_INTERRUPT_HANDLER(8);
NEW_INTERRUPT_HANDLER(9);
NEW_INTERRUPT_HANDLER(10);
NEW_INTERRUPT_HANDLER(11);
NEW_INTERRUPT_HANDLER(12);
NEW_INTERRUPT_HANDLER(13);
NEW_INTERRUPT_HANDLER(14);
NEW_INTERRUPT_HANDLER(15);
NEW_INTERRUPT_HANDLER(16);
NEW_INTERRUPT_HANDLER(17);
NEW_INTERRUPT_HANDLER(18);
NEW_INTERRUPT_HANDLER(19);
NEW_INTERRUPT_HANDLER(20);

NEW_INTERRUPT_HANDLER(21);
NEW_INTERRUPT_HANDLER(22);
NEW_INTERRUPT_HANDLER(23);
NEW_INTERRUPT_HANDLER(24);
NEW_INTERRUPT_HANDLER(25);
NEW_INTERRUPT_HANDLER(26);
NEW_INTERRUPT_HANDLER(27);
NEW_INTERRUPT_HANDLER(28);
NEW_INTERRUPT_HANDLER(29);
NEW_INTERRUPT_HANDLER(30);
NEW_INTERRUPT_HANDLER(31);

// IRQ interrupts typically go from 32-47
NEW_INTERRUPT_HANDLER(32);
NEW_INTERRUPT_HANDLER(33);
NEW_INTERRUPT_HANDLER(34);
NEW_INTERRUPT_HANDLER(35);
NEW_INTERRUPT_HANDLER(36);
NEW_INTERRUPT_HANDLER(37);
NEW_INTERRUPT_HANDLER(38);
NEW_INTERRUPT_HANDLER(39);
NEW_INTERRUPT_HANDLER(40);
NEW_INTERRUPT_HANDLER(41);
NEW_INTERRUPT_HANDLER(42);
NEW_INTERRUPT_HANDLER(43);
NEW_INTERRUPT_HANDLER(44);
NEW_INTERRUPT_HANDLER(45);
NEW_INTERRUPT_HANDLER(46);
NEW_INTERRUPT_HANDLER(47);

void (*handlers[256])() = { NULL };

/*
 * General interrupt handler that takes in the interrupt number and sends it
 * to the appropriate handler
 */
void interrupt_handler(struct interrupt_data data)
{
	if(handlers[data.int_num] != NULL) {
		handlers[data.int_num]();
	} else if(data.int_num < 32) {
		
		printf("Interrupt: %i\tErr #: %i\n", (int)data.int_num, (int)data.error_code);
		printf("EAX: %x\tEBX: %x\tECX: %x\tEDX: %x\n", (unsigned int)data.eax, (unsigned int)data.ebx, (unsigned int)data.ecx, (unsigned int)data.edx);
		printf("ESP: %x\tEBP: %x\tESI: %x\tEDI: %x\n", (unsigned int)data.esp, (unsigned int)data.ebp, (unsigned int)data.esi, (unsigned int)data.edi);
		printf("EIP: %x\tCS: %x\tFLAGS: %x\tUESP: %x\n", (unsigned int)data.eip, (unsigned int)data.cs, (unsigned int)data.eflags, (unsigned int)data.useresp);
		printf("SS: %x\tDS: %x\n", (unsigned int)data.ss, (unsigned int)data.ds);

		abort();
	}
}

void idt_set_gate(uint8_t index, uint32_t isr_adr, uint16_t selector, uint8_t flags)
{
	idt[index].offset1 = (isr_adr & 0xFFFF);
	idt[index].offset2 = ((isr_adr >> 16) & 0xFFFF);
	idt[index].selector = selector;
	idt[index].gate_type = flags & 0xF;
	idt[index].storage_segment = (flags >> 4) & 0x1;
	idt[index].dpl = (flags >> 5) & 0x3;
	idt[index].present = (flags >> 7) & 0x1;
	idt[index].zero = 0;
}

void idt_install_handler(uint8_t int_num, void (*handler)())
{
	handlers[int_num] = handler;
}

void idt_init()
{
	disable_interrupts();

	idt = (struct idt_entry_t*)idt_contents;

	// exceptions
	IDT_SET_GATE(0);
	IDT_SET_GATE(1);
	IDT_SET_GATE(2);
	IDT_SET_GATE(3);
	IDT_SET_GATE(4);
	IDT_SET_GATE(5);
	IDT_SET_GATE(6);
	IDT_SET_GATE(7);
	IDT_SET_GATE(8);
	IDT_SET_GATE(9);
	IDT_SET_GATE(10);
	IDT_SET_GATE(11);
	IDT_SET_GATE(12);
	IDT_SET_GATE(13);
	IDT_SET_GATE(14);
	IDT_SET_GATE(15);
	IDT_SET_GATE(16);
	IDT_SET_GATE(17);
	IDT_SET_GATE(18);
	IDT_SET_GATE(19);
	IDT_SET_GATE(20);

	IDT_SET_GATE(21);
	IDT_SET_GATE(22);
	IDT_SET_GATE(23);
	IDT_SET_GATE(24);
	IDT_SET_GATE(25);
	IDT_SET_GATE(26);
	IDT_SET_GATE(27);
	IDT_SET_GATE(28);
	IDT_SET_GATE(29);
	IDT_SET_GATE(30);
	IDT_SET_GATE(31);

	// IRQ's
	IDT_SET_GATE(32);
	IDT_SET_GATE(33);
	IDT_SET_GATE(34);
	IDT_SET_GATE(35);
	IDT_SET_GATE(36);
	IDT_SET_GATE(37);
	IDT_SET_GATE(38);
	IDT_SET_GATE(39);
	IDT_SET_GATE(40);
	IDT_SET_GATE(41);
	IDT_SET_GATE(42);
	IDT_SET_GATE(43);
	IDT_SET_GATE(44);
	IDT_SET_GATE(45);
	IDT_SET_GATE(46);
	IDT_SET_GATE(47);

	idt_ptr = (struct idt_pointer_t*)idt_pointer;
	idt_ptr->limit = (uint16_t)((256 * sizeof(struct idt_entry_t)) -1);
	idt_ptr->base = idt;

	__asm__
	(
		"mov eax, [idt_pointer]\n"
		"lidt [eax]"
	);
}
