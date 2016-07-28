
#define outb(PORT, VALUE) __asm__("mov al, " #VALUE "\n" "outb " #PORT ", al\n");
