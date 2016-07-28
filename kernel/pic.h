#define PICM_COMMAND 0x20 // new offset for master PIC
#define PICM_DATA (PICM_COMMAND+1)
#define PICS_COMMAND 0xA0 // new offset for slave PIC
#define PICS_DATA (PICS_COMMAND+1)

#define PIC_EOI 0x20

static inline void outb(uint16_t port, uint8_t value)
{
	asm(".att_syntax prefix");
	asm volatile ( "outb %0, %1" : : "a"(value), "Nd"(port) );
	asm(".intel_syntax noprefix");
}

void pic_map(int offset1, int offset2);
