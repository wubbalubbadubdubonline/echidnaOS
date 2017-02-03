enter_pmode:

; Since we're using paging, setup the page directory (map first 4 MiB of RAM)

mov edi, 0x1000			; Clear the 2 pages (PDT, and PT)
mov cr3, edi
xor eax, eax
mov ecx, 0x800
a32 o32 rep stosd

mov dword [0x1000], 0x2003	; Point the PDT to the PT

; Map the first 4 MiB in the PT

mov edi, 0x2000
mov ebx, 0x00000003
mov ecx, 1024
.mapPTloop:
mov dword [es:edi], ebx
add ebx, 0x1000
add edi, 4
loop .mapPTloop

cli						; Disable interrupts

mov eax, cr0			; Enable bit 31 and 0 of cr0 and enter paged protected mode
or eax, 0x80000001
mov cr0, eax

jmp 0x18:.pmode

bits 32

.pmode:					; Now in protected mode

mov ax, 0x20
mov ds, ax
mov es, ax
mov fs, ax
mov gs, ax
mov ss, ax
