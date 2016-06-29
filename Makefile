iso := build/hobby-os.iso
kernel := build/kernel.bin

grub_cfg := kernel/grub.cfg

all: kernel.bin

boot.o: kernel/boot.asm
	nasm -felf32 kernel/boot.asm -o boot.o

kernel.bin: boot.o kernel/linker.ld
	i686-elf-gcc -T kernel/linker.ld -o $(kernel) -ffreestanding -O2 -nostdlib boot.o -lgcc

iso: $(iso)

$(iso): $(kernel) $(grub_cfg)
	@mkdir -p build/isofiles/boot/grub
	@cp $(kernel) build/isofiles/boot/kernel.bin
	@cp $(grub_cfg) build/isofiles/boot/grub
	@grub-mkrescue -o $(iso) build/isofiles 2> /dev/null
	@rm -r build/isofiles
