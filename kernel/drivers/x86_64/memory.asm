global mem_get_block_base
global mem_get_block_size

section .data

section .text

bits 64

mem_get_block_base:
	mov rax, 24
	mul rdi
	mov rax, qword [rax+0x5000]
	xor rdx, rdx
	ret

mem_get_block_size:
	mov rax, 24
	mul rdi
	mov rax, qword [rax+0x5008]
	xor rdx, rdx
	ret
