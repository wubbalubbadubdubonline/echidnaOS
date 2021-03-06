org 0x7C00						; BIOS loads us here (0000:7C00)
bits 16							; 16-bit real mode code

%include 'bootloader/includes/bootloader.inc'


arch_specific:

%include 'bootloader/includes/enter_pmode.inc'		; Enter Protected Mode

; *** Setup registers ***

xor eax, eax
xor ebx, ebx
xor ecx, ecx
xor edx, edx
xor esi, esi
xor edi, edi
xor ebp, ebp

mov esp, 0xFFFFFFF0

jmp 0xC0000000					; Jump to the newly loaded kernel

times 4096-($-$$)			db 0x00				; Padding
