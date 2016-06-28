bits 32
align 4

global _boot_start

section .text

; BEGIN - Initialize the multiboot header
MAGIC dd 0x1BADB002 ; Magic number provided in the multiboot specification
FLAGS dd (1 << 0) | (1 << 1) ; Align memory to 4KB boundaries and provide multiboot info structure
CHECKSUM dd -(MAGIC + FLAGS)
; END - multiboot header

stack_bottom:
	db 65536 ; Allocate memory for the stack 
stack_top:

_boot_start:
	cli
	
	mov dword ebx, 0x2BADB002
	cmp eax, ebx ; If multiboot loaded correctly, 0x2BADB002 will be in eax
	jne multiboot_error ; Handle the error if multiboot doesn't load for some reason

	mov dword ebx, cr0		; Enable protected mode by setting the first bit of cr0
	or ebx, 1
	mov dword cr0, ebx

	mov esp, stack_top	; Set the stack pointer to the top of the stack (stack grows downward)

; handle multiboot issue
multiboot_error:

; Hang kernel in loop
hang:
	hlt
	jmp hang
