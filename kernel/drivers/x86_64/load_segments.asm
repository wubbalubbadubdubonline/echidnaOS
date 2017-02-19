global load_segments

section .data

far_jump_target:
	dq load_segments.load_cs
	dw 0x08

section .text

bits 64

load_segments:
	jmp far [far_jump_target]
	.load_cs:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	ret
