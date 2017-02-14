global map_page

section .data

phys_addr	dd	0
virt_addr	dd	0

section .text

bits 32

map_page:
	mov eax, [esp+4]
	mov dword [phys_addr], eax
	mov eax, [esp+8]
	mov dword [virt_addr], eax
	ret
