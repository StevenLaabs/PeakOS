#include "pic.h"

void pic_map(int offset1, int offset2)
{
	__asm__
	(
		"cli\n"
		"nop\n"
	);

	// initialize
	outb(0x20, 0x11);
	outb(0xA0, 0x11);

	// ICW2
	outb(0x21, offset1);
	outb(0xA1, offset2);

	// ICW3
	outb(0x21, 0x04);
	outb(0xA1, 0x02);

	outb(0x21, 0x01);
	outb(0xA1, 0x01);

	outb(0x21, 0xFF);
	outb(0xA1, 0xFF);

	__asm__
	(
		"sti\n"
		"nop\n"
	);
}
