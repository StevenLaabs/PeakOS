# Reference for this makefile comes from: http://wiki.osdev.org/Meaty_Skeleton#Makefile_Design

HOST ?= i686-elf
HOSTARCH := $(shell ../target-triplet-to-arch.sh $(HOST))

CFLAGS?=-O2 -g -Iinclude
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
LIBDIR:=libk

include $(ARCHDIR)/make.config
include $(LIBDIR)/make.config

CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS) $(LIBK_CFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS) $(LIBK_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS) $(LIBK_LIBS)

OBJS:=\
$(KERNEL_ARCH_OBJS) \
$(LIBK_OBJS) \
main.o \
terminal.o \
paging.o \
pmm.o \
drivers/keyboard.o \
drivers/de9.o \
hal/io.o \
hal/pic.o \
hal/idt_asm.o \
hal/idt.o \
hal/hal.o \

all: peakos.kernel

.PHONY: all clean install

peakos.kernel: $(OBJS) $(ARCHDIR)/linker.ld
	i686-elf-gcc -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) $(OBJS) $(LDFLAGS) $(LIBS)

%.o: %.c
	i686-elf-gcc -c -masm=intel $< -o $@ -std=gnu11 $(CFLAGS)

%.o: %.asm
	nasm -felf32 $< -o $@

clean:
	rm -f peakos.kernel $(OBJS) *.o */*.o */*/*.o

install: peakos.kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp peakos.kernel $(DESTDIR)$(BOOTDIR)
