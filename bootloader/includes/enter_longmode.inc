enter_longmode:

; Since we're using paging, setup the page directory (map first 2 MiB of RAM)

mov edi, 0x1000			; Clear the 4 pages (PML4T, PDPT, PDT, and PT)
mov cr3, edi
xor eax, eax
mov ecx, 0x1000
a32 o32 rep stosd

mov dword [0x1000], 0x2003	; Point the PML4T to the PDPT
mov dword [0x2000], 0x3003	; Point the PDPT to the PPT
mov dword [0x3000], 0x4003	; Point the PDT to the PT

; Map the first 2 MiB in the PT

mov edi, 0x4000
mov ebx, 0x00000003
mov ecx, 512
.mapPTloop:
mov dword [es:edi], ebx
add ebx, 0x1000
add edi, 8
loop .mapPTloop

cli						; Disable interrupts

mov eax, cr4			; Enable PAE
or eax, 00100000b
mov cr4, eax

mov ecx, 0xC0000080		; Enable the long mode bit
rdmsr
or eax, 100000000b
wrmsr

mov eax, cr0			; Enable bit 31 and 0 of cr0 and enter long mode
or eax, 0x80000001
mov cr0, eax

jmp 0x28:.longmode

bits 64

.longmode:				; Now in 64-bit long mode

mov ax, 0x30
mov ds, ax
mov es, ax
mov fs, ax
mov gs, ax
mov ss, ax
