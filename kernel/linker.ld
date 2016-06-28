ENTRY(_boot_start)

SECTIONS {
	. = 1M;

	.boot : {
		*(.multiboot);
	}

	.text : {
		*(.text);
	}
}
