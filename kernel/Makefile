iso := build/hobby-os.iso
kernel := kernel.bin

grub_cfg := kernel/grub.cfg

all: kernel.bin

%.o: %.asm
	nasm -felf32 $< -o $@

%.o: %.c
	i686-elf-gcc -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

kernel.bin: boot.o main.o linker.ld
	i686-elf-gcc -T linker.ld -o $(kernel) -ffreestanding -O2 -nostdlib boot.o main.o -lgcc
