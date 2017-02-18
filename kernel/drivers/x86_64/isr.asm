global handler_simple
global handler_code
global handler_irq_pic0
global handler_irq_pic1
global keyboard_isr

section .data

section .text

bits 64

handler_simple:
	iretq

handler_code:
	add rsp, 4
	iretq

handler_irq_pic0:
	push rax
	mov al, 0x20	; acknowledge interrupt to PIC0
	out 0x20, al
	pop rax
	iretq

handler_irq_pic1:
	push rax
	mov al, 0x20	; acknowledge interrupt to both PICs
	out 0xA0, al
	out 0x20, al
	pop rax
	iretq

keyboard_isr:
	xchg bx, bx
	push rax
	in al, 0x60		; read from keyboard
	mov al, 0x20	; acknowledge interrupt to PIC0
	out 0x20, al
	pop rax
	iretq
