global handler_simple
global handler_code
global handler_irq_pic0
global handler_irq_pic1
global keyboard_isr

section .data

section .text

bits 32

handler_simple:
	iret

handler_code:
	add esp, 4
	iret

handler_irq_pic0:
	push eax
	mov al, 0x20	; acknowledge interrupt to PIC0
	out 0x20, al
	pop eax
	iret

handler_irq_pic1:
	push eax
	mov al, 0x20	; acknowledge interrupt to both PICs
	out 0xA0, al
	out 0x20, al
	pop eax
	iret

keyboard_isr:
	xchg bx, bx
	push eax
	in al, 0x60		; read from keyboard
	mov al, 0x20	; acknowledge interrupt to PIC0
	out 0x20, al
	pop eax
	iret
