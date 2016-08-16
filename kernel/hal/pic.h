#ifndef _PIC_H
#define _PIC_H

#include <stdint.h>

#define IRQ_TIMER 0
#define IRQ_KEYBOARD 1

/*
 * Maps the PIC interrupt numbers to the corresponding offsets and initializes them
 * by configuring the ICW registers (see: https://pdos.csail.mit.edu/6.828/2010/readings/hardware/8259A.pdf)
 */
void pic_map(int offset1, int offset2);

/*
 * Masks the bit for the indicated IRQ number to disable the IRQ
 */
void irq_mask(uint8_t irq);

/*
 * Unmasks the bit for the indicated IRQ number to enable the IRQ
 */
void irq_unmask(uint8_t irq);

/*
 * Sends the EOI signal for the IRQ so that the IRQ can be completed
 */
void irq_send_eoi(uint8_t irq);

#endif
