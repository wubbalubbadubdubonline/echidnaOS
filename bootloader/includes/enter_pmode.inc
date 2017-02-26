enter_pmode:

; Since we're using paging, setup the page directory

; (identity map the first 4 MiBs of RAM, map kernel at 0xC0000000, kernel stack at 0xFFFFFFF0)

mov edi, 0x100000			; Clear the PDT
mov cr3, edi
xor eax, eax
mov ecx, 0x400
a32 o32 rep stosd

a32 o32 mov dword [0x100000], 0x83		; (first 4 MiBs)
a32 o32 mov dword [0x100C00], 0x1000083	; (kernel)
a32 o32 mov dword [0x100FFC], 0x800083	; (kernel stack)
a32 o32 mov dword [0x100FF8], 0x400083	; (more kernel stack)

cli						; Disable interrupts

mov eax, cr4			; Enable PSE
or eax, 10000b
mov cr4, eax

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
