global mem_get_block_base
global mem_get_block_size
global mem_get_block_type
global mem_get_block_ext

section .data

section .text

bits 32

mem_get_block_base:
	mov eax, 24
	mul dword [esp+4]
	mov eax, dword [eax+0x5000]
	ret

mem_get_block_size:
	mov eax, 24
	mul dword [esp+4]
	mov eax, dword [eax+0x5008]
	ret

mem_get_block_type:
	mov eax, 24
	mul dword [esp+4]
	mov eax, dword [eax+0x5010]
	ret

mem_get_block_ext:
	mov eax, 24
	mul dword [esp+4]
	mov eax, dword [eax+0x5014]
	ret
