#include <hal.h>
#include <stdio.h>

#include "idt.h"
#include "pic.h"

void hal_init()
{
    idt_init();

    pic_map(0x20, 0x28);

	enable_interrupts();
}

void enable_interrupts()
{
    __asm__
    (
        "sti\n"
        "nop\n"
    );
}

void disable_interrupts()
{
    __asm__
    (
        "cli\n"
        "nop\n"
    );
}

void irq_install(uint8_t irq_num, void (*handler)())
{
    irq_unmask(irq_num);
    idt_install_handler(irq_num + 32, handler);
}

void interrupt_complete(uint8_t irq_num)
{
    if(irq_num > 16)
        return;

    irq_send_eoi(irq_num);
}
