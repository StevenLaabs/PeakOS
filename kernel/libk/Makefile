HOSTARCH:=i386

CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

CFLAGS:=$(CFLAGS) -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_myos_libc -Iinclude
LIBK_CFLAGS:=$(CFLAGS) -ffreestanding -fbuiltin
LIBK_CPPFLAGS:=$(CPPFLAGS) -D__is_myos_kernel
 
ARCHDIR:=arch/$(HOSTARCH)
 
 include $(ARCHDIR)/make.config
  
CFLAGS:=$(CFLAGS) $(ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(ARCH_CPPFLAGS)
LIBK_CFLAGS:=$(LIBK_CFLAGS) $(KERNEL_ARCH_CFLAGS)
LIBK_CPPFLAGS:=$(LIBK_CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)

FREEOBJS:=\
$(ARCH_FREEOBJS) \
stdio/printf.o \
stdio/putchar.o \
stdio/puts.o \
stdlib/abort.o \
stdlib/atoi.o \
string/memchr.o \
string/memcmp.o \
string/memcpy.o \
string/memmove.o \
string/memset.o \
string/strlen.o \
string/strcmp.o \
string/strcat.o \
string/strcpy.o \
	 
HOSTEDOBJS:=\
	$(ARCH_HOSTEDOBJS) \

OBJS:=\
	$(FREEOBJS) \
	$(HOSTEDOBJS) \

all: libc.a

.PHONY: all clean

libc.a: $(OBJS)
	i686-elf-ar rcs $@ $(OBJS)

%.o: %.c
	i686-elf-gcc -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)
		 
%.o: %.asm
	i686-elf-gcc -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

clean:
	rm -f libc.a $(OBJS) *.o */*.o */*/*.o
