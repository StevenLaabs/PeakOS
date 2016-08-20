section .text

EXTERN interrupt_handler

%macro interrupt_handler_macro 1
GLOBAL interrupt_handler_%1

; Common interrupt handler which will call the C handler
interrupt_handler_%1:
	push dword %1 ; push interrupt number for argument
	pushad

	mov ax, ds
	push eax      ; push the data segment for argument

	call interrupt_handler
	add esp, 4

	pop eax

	popad

	iret
%endmacro

interrupt_handler_macro 0
interrupt_handler_macro 1
interrupt_handler_macro 2
interrupt_handler_macro 3
interrupt_handler_macro 4
interrupt_handler_macro 5
interrupt_handler_macro 6
interrupt_handler_macro 7
interrupt_handler_macro 8
interrupt_handler_macro 9
interrupt_handler_macro 10
interrupt_handler_macro 11
interrupt_handler_macro 12
interrupt_handler_macro 13
interrupt_handler_macro 14
interrupt_handler_macro 15
interrupt_handler_macro 16
interrupt_handler_macro 17
interrupt_handler_macro 18
interrupt_handler_macro 19
interrupt_handler_macro 20

interrupt_handler_macro 21
interrupt_handler_macro 22
interrupt_handler_macro 23
interrupt_handler_macro 24
interrupt_handler_macro 25
interrupt_handler_macro 26
interrupt_handler_macro 27
interrupt_handler_macro 28
interrupt_handler_macro 29
interrupt_handler_macro 30
interrupt_handler_macro 31

interrupt_handler_macro 32
interrupt_handler_macro 33
interrupt_handler_macro 34
interrupt_handler_macro 35
interrupt_handler_macro 36
interrupt_handler_macro 37
interrupt_handler_macro 38
interrupt_handler_macro 39
interrupt_handler_macro 40
interrupt_handler_macro 41
interrupt_handler_macro 42
interrupt_handler_macro 43
interrupt_handler_macro 44
interrupt_handler_macro 45
interrupt_handler_macro 46
interrupt_handler_macro 47
