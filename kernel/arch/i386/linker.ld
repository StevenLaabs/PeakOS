ENTRY(_boot_start)

SECTIONS {
	. = 0xC0100000;

	.text : AT(ADDR(.text) - 0xC0000000) {
		/* Put multiboot header at the beginning of memory so it is recognized */
		*(.multiboot)
		*(.text)
	}

	/* .bss is Read-write data that is uninitialized and stack */
	.bss ALIGN(4k) : AT(ADDR(.bss) - 0xC0000000) {
		*(.bss)
	}
}
