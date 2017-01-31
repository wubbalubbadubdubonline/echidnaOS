enter_pmode:

cli						; Disable interrupts

mov eax, cr0			; Enable bit 0 of cr0 and enter protected mode
or eax, 00000001b
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
