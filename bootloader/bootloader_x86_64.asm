org 0x7C00						; BIOS loads us here (0000:7C00)
bits 16							; 16-bit real mode code

%include 'bootloader/includes/bootloader.inc'


arch_specific:

%include 'bootloader/includes/enter_longmode.inc'		; Enter Long Mode

; *** Setup registers ***

xor rax, rax
xor rbx, rbx
xor rcx, rcx
xor rdx, rdx
xor rsi, rsi
xor rdi, rdi
xor rbp, rbp

mov rsp, 0x1FFFF0				; Stack at 2MiB

jmp 0x100000					; Jump to the newly loaded kernel

times 4096-($-$$)			db 0x00				; Padding
