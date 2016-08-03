#include <kernel/pic.h>

void pic_map(int offset1, int offset2)
{
	__asm__
	(
		"cli\n"
		"nop\n"
	);

	// initialize
	outb(PICM_COMMAND, 0x11);
	outb(PICS_COMMAND, 0x11);

	// ICW2
	outb(PICM_DATA, offset1);
	outb(PICS_DATA, offset2);

	// ICW3
	outb(PICM_DATA, 0x04);
	outb(PICS_DATA, 0x02);

	outb(PICM_DATA, 0x01);
	outb(PICS_DATA, 0x01);

	outb(PICM_DATA, 0xFF);
	outb(PICS_DATA, 0xFF);

	__asm__
	(
		"sti\n"
		"nop\n"
	);
}

void irq_mask(uint8_t irq)
{
	uint16_t port;
	uint8_t value;

	if(irq < 8) {
		port = PICM_DATA;
	} else {
		// IRQs 8-15 are on the slave PIC
		port = PICS_DATA;
		irq -= 8;
	}

	value = inb(port) | (1 << irq); // set the bit correspond to the irq number
	outb(port, value);              // output the new value with the proper bit set
}

void irq_unmask(uint8_t irq)
{
	uint16_t port;
	uint8_t value;

	if(irq < 8) {
		port = PICM_DATA;
	} else {
		// IRQs 8-15 are on slave PIC
		port = PICS_DATA;
		irq -= 8;
	}

	// set all masked bits to 1 except the one we wish to disable then and it
	// with the current port value
	value = inb(port) & ~(1 << irq);
	outb(port, value);
}

void irq_send_eoi(uint8_t irq)
{
	if(irq >= 8)
		outb(PICS_COMMAND, PIC_EOI);

	outb(PICM_COMMAND, PIC_EOI); // end of interrupt
}
