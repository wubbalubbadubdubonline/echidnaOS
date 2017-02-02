org 0x7C00						; BIOS loads us here (0000:7C00)
bits 16							; 16-bit real mode code

%include 'bootloader/includes/bootloader.inc'


arch_specific:

%include 'bootloader/includes/enter_pmode.inc'		; Enter Protected Mode

; *** Setup registers ***

xor eax, eax
xor ebx, ebx
xor ecx, ecx
and edx, 0x000000FF
xor esi, esi
xor edi, edi
xor ebp, ebp

mov esp, 0x500000				; Stack at 5MB

jmp 0x100000					; Jump to the newly loaded kernel

times 4096-($-$$)			db 0x00				; Padding
