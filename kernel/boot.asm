BITS 32

MAGIC equ 0x1BADB002                            ; Magic number provided in the multiboot specification

PAGEALIGN equ (1 << 0)                          ; Align memory to 4KB boundaries
MEMINFO equ (1 << 1)                            ; Provide multiboot info structure
FLAGS equ PAGEALIGN | MEMINFO                   ; Multiboot header flags

CHECKSUM equ -(MAGIC + FLAGS)

section .__mbHeader
align 4

dd MAGIC
dd FLAGS
dd CHECKSUM

section .text
GLOBAL _boot_start

; BEGIN - configure multiboot 
multiboot_mem_high dd 0
multiboot_mem_low dd 0
multiboot_info_structure dd 0
; END - multiboot configured

stack_bottom:
	times 65536 db 0                            ; Allocate 64 KiB memory for the stack 
stack_top:

_boot_start:
	cli

	; BEGIN - check multiboot load
	mov dword ecx, 0x2BADB002
	cmp eax, ecx                                ; If multiboot loaded correctly, 0x2BADB002 will be in eax
	jne multiboot_error                         ; Handle the error if multiboot doesn't load for some reason
	; END - check multiboot load

	; BEGIN - save info from the multiboot info structure
	mov dword [multiboot_info_structure], ebx   ; ebx contains address of multiboot info structure
	add dword ebx, 0x4                          ; set ebx to the mem_lower bits in the info structure
	mov dword eax, [ebx]                        ; set eax to the mem_lower values 
	mov dword [multiboot_mem_low], eax          ; save the mem_lower values to multiboot_mem_low
	add dword ebx, 0x4                          ; set ebx to the mem_upper bits in the info structure
	mov dword eax, [ebx]                        ; set eax to the mem_upper values
	mov dword [multiboot_mem_high], eax         ; save the mem_upper values to multiboot_mem_high
	; END - save multiboot info structure

	; BEGIN - set protected mode
	mov dword ebx, cr0                          ; Enable protected mode by setting the first bit of cr0
	or ebx, 1
	mov dword cr0, ebx
	; END - protected mode set

	mov esp, stack_top                          ; Set the stack pointer to the top of the stack 
	
	jmp hang

; handle multiboot issue
multiboot_error:
	mov al, "0"
	jmp error_msg

; TODO: Do printing in asm in a better way than this
error_msg:
	mov dword [0xB8000], 0x4f524f45
	mov dword [0xB8004], 0x4f3a4f52
	mov dword [0xB8008], 0x4f204f20
	mov byte [0xB800A], al
	hlt

; Hang kernel in loop
hang:
	cli

	mov dword [0xB8000], 0x4f524f45

	hlt
	jmp hang

