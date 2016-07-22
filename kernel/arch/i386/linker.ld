ENTRY(_boot_start)

SECTIONS {
	. = 0x1M;

	.text ALIGN(4k) : {
		/* Put multiboot header at the beginning of memory so it is recognized */
		*(.multiboot)
		*(.text)
	}

	/* .data is Read-write data that is initialized */
	.data ALIGN(4k) : {
		*(.data)
	}	

	/* .bss is Read-write data that is uninitialized and stack */
	.bss ALIGN(4k) : {
		*(.bss)
	}
}
