#include <kernel/idt.h>
#include <kernel/terminal.h>
#include <kernel/pic.h>
#include <drivers/keyboard.h>

// macro defines a function for the interrupt handler number
#define NEW_INTERRUPT_HANDLER(i) extern void interrupt_handler_##i(void)

#define IDT_SET_GATE(index) idt_set_gate(index, (uint32_t)&interrupt_handler_##index, 0x08, 0x8E);

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

void interrupt_handler(struct interrupt_data data)
{
	if(data.int_num == 32) {
		// this is the timer
	} else if(data.int_num == 33) {
		keyboard_handler();
	}

	if(data.int_num >= 32 && data.int_num < 48) {
		irq_send_eoi(data.int_num - 32);
	} else if(data.int_num < 32) {
		terminal_write("Interrupt: ");
		terminal_writeint(data.int_num, 10);
		terminal_write(" Err #: ");
		terminal_writeint(data.error_code, 10);
		terminal_putchar('\n');

		terminal_write("EAX: ");
		terminal_writeint(data.eax, 16);
		terminal_write(" EBX: ");
		terminal_writeint(data.ebx, 16);
		terminal_write(" ECX: ");
		terminal_writeint(data.ecx, 16);
		terminal_write(" EDX: ");
		terminal_writeint(data.edx, 16);

		terminal_write("\nESP: ");
		terminal_writeint(data.esp, 16);
		terminal_write(" EBP: ");
		terminal_writeint(data.ebp, 16);
		terminal_write(" ESI: ");
		terminal_writeint(data.esi, 16);
		terminal_write(" EDI: ");
		terminal_writeint(data.edi, 16);

		terminal_write("\nEIP: ");
		terminal_writeint(data.eip, 16);
		terminal_write(" CS: ");
		terminal_writeint(data.cs, 16);
		terminal_write(" FLAGS: ");
		terminal_writeint(data.eflags, 16);
		terminal_write(" UESP: ");
		terminal_writeint(data.useresp, 16);
		terminal_write(" SS: ");
		terminal_writeint(data.ss, 16);

		terminal_write("\nDS: ");
		terminal_writeint(data.ds, 16);
		terminal_putchar('\n');

		// TODO: kernel abort/panic method in libk
		asm("cli");
		terminal_write("\nPanic! Aborting...\n");
		while(1) {}
	}
}

void idt_set_gate(uint8_t index, uint32_t isr_adr, uint16_t selector, uint8_t flags)
{
	idt[index].offset1 = (isr_adr & 0xFFFF);
	idt[index].offset2 = ((isr_adr >> 16) & 0xFFFF);
	idt[index].selector = selector;
	idt[index].gate_type = 0xE;
	idt[index].storage_segment = 0x0;
	idt[index].dpl = 0x0;
	idt[index].present = 0x1;
	idt[index].zero = 0;
}

void idt_init()
{
	__asm__
	(
		"cli\n"
		"nop\n"
	);

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

	pic_map(0x20, 0x28);

	// unmask the timer and keyboard IRQs so they can be used
	irq_unmask(IRQ_TIMER);
	irq_unmask(IRQ_KEYBOARD);

	// configure PIT to be slow rate generator
	outb(PIT_CMD_PORT, 0x34);
	outb(PIT_CH0_PORT, 0xFF);
	outb(PIT_CH0_PORT, 0xFF);

	__asm__
	(
		"sti\n"
		"nop\n"
	);
}
