ENTRY(_boot_start)

SECTIONS {
	. = 0x100000;

	.__mbHeader : {
		*(.__mbHeader)
	}

	.text : {
		*(multiboot)
		*(.text)
	}
}
