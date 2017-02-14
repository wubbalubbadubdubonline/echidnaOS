global map_page

section .data

phys_addr	dq	0
virt_addr	dq	0

section .text

bits 64

map_page:
	mov qword [phys_addr], rdi
	mov qword [virt_addr], rsi
	ret
