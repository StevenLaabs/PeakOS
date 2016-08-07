ENTRY(_boot_start)

SECTIONS {
	. = 0xC0100000;

	start_kernel_virtual = .;
	start_kernel_physical = . - 0xC0000000;

	.text : AT(ADDR(.text) - 0xC0000000) {
		/* Put multiboot header at the beginning of memory so it is recognized */
		*(.multiboot)
		*(.text)
		*(.rodata*)
	}

	/* .data is Read-write data that is initialized */
	.data ALIGN(4k) : AT(ADDR(.data) - 0xC0000000) {
		*(.data)
	}

	/* .bss is Read-write data that is uninitialized and stack */
	.bss ALIGN(4k) : AT(ADDR(.bss) - 0xC0000000) {
		*(.bss)
	}

	end_kernel_virtual = .;
	end_kernel_physical = . - 0xC0000000;
}
