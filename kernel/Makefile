# Reference for this makefile comes from: http://wiki.osdev.org/Meaty_Skeleton#Makefile_Design

HOST ?= i686-elf
HOSTARCH := $(shell ../target-triplet-to-arch.sh $(HOST))

CFLAGS?=-O2 -g
LDFLAGS?=
LIBS?=

DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include

CFLAGS:=$(CFLAGS) -ffreestanding -fbuiltin -Wall -Wextra
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS) -nostdlib -lgcc

ARCHDIR:=arch/$(HOSTARCH)

include $(ARCHDIR)/make.config
 
CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)

OBJS:=\
$(KERNEL_ARCH_OBJS) \
main.o \
terminal.o \
paging.o \
pic.o \
idt_asm.o \
idt.o \

all: hobby-os.kernel

.PHONY: all clean install

hobby-os.kernel: $(OBJS) $(ARCHDIR)/linker.ld
	i686-elf-gcc -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) $(OBJS) $(LDFLAGS) $(LIBS)

%.o: %.c
	i686-elf-gcc -c -masm=intel $< -o $@ -std=gnu11 $(CFLAGS)
 
%.o: %.asm
	nasm -felf32 $< -o $@

clean:
	rm -f hobby-os.kernel $(OBJS) *.o */*.o */*/*.o
 
install: hobby-os.kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp hobby-os.kernel $(DESTDIR)$(BOOTDIR)
