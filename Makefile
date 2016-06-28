iso := build/hobby-os.iso
kernel := build/kernel.bin

grub_cfg := kernel/grub.cfg

all: kernel.bin

boot.o: kernel/boot.asm
	nasm -g -f elf64 -o boot.o kernel/boot.asm

kernel.bin: boot.o kernel/linker.ld
	ld -n -o $(kernel) -T kernel/linker.ld boot.o

iso: $(iso)

$(iso): $(kernel) $(grub_cfg)
	@mkdir -p build/isofiles/boot/grub
	@cp $(kernel) build/isofiles/boot/kernel.bin
	@cp $(grub_cfg) build/isofiles/boot/grub
	@grub-mkrescue -o $(iso) build/isofiles 2> /dev/null
	@rm -r build/isofiles
