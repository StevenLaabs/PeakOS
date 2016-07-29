#include "io.h"

#define PICM_COMMAND 0x20 // new offset for master PIC
#define PICM_DATA (PICM_COMMAND+1)
#define PICS_COMMAND 0xA0 // new offset for slave PIC
#define PICS_DATA (PICS_COMMAND+1)

#define PIC_EOI 0x20

#define IRQ_TIMER 0
#define IRQ_KEYBOARD 1

void pic_map(int offset1, int offset2);

void irq_mask(uint8_t irq);
void irq_unmask(uint8_t irq);

void irq_send_eoi(uint8_t irq);
