ENTRY(_boot_start)

SECTIONS {
	. = 0x100000;

	.multiboot : {
		*(.multiboot)
	}

	.text : {
		*(.text)
	}
}
