enter_pmode:

; Since we're using paging, setup the page directory

; (identity map the first MiB of RAM, map kernel at 0xC0000000, kernel stack at 0xFFFFFFF0)

mov edi, 0x1000			; Clear the PDT, and PT
mov cr3, edi
xor eax, eax
mov ecx, 0x800
a32 o32 rep stosd

mov dword [0x1000], 0x2003		; Point the PDT to the PT for the first MiB
mov dword [0x1C00], 0x800083	; (kernel)
mov dword [0x1FFC], 0x400083	; (kernel stack)

; Map the first MiB in the PT

mov edi, 0x2000
mov ebx, 0x00000003
mov ecx, 256
.mapPTloop:
mov dword [es:edi], ebx
add ebx, 0x1000
add edi, 4
loop .mapPTloop

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
