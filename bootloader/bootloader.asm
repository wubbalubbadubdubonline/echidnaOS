org 0x7C00						; BIOS loads us here (0000:7C00)
bits 16							; 16-bit real mode code

jmp short code_start			; Jump to the start of the code
nop								; Pad with NOP instruction
times 3-($-$$) db 0x00			; Make sure this is the start of the BPB

; The BPB starts here

bpbOEM						db 'ECHIDNA '
bpbBytesPerSector			dw 512
bpbSectorsPerCluster		db 1
bpbReservedSectors			dw 8
bpbNumberOfFATs				db 2
bpbRootEntries				dw 224
bpbTotalSectors				dw 2880
bpbMedia					db 0xF8
bpbSectorsPerFAT			dw 9
bpbSectorsPerTrack			dw 18
bpbHeadsPerCylinder			dw 2
bpbHiddenSectors			dd 0
bpbTotalSectorsBig			dd 0
bsDriveNumber				db 0x00
bsUnused					db 0x00
bsExtBootSignature			db 0x29
bsSerialNumber				dd 0x12345678
bsVolumeLabel				db 'ECHIDNA OS '
bsFileSystem				db 'FAT12   '

; End of BPB, start of main bootloader code

code_start:

cli
jmp 0x0000:initialise_cs		; Initialise CS to 0x0000 with a long jump
initialise_cs:
xor ax, ax
mov ds, ax
mov es, ax
mov fs, ax
mov gs, ax
mov ax, 0x8000
mov ss, ax
mov sp, 0xFFF0
sti

mov si, LoadingMsg				; Print loading message using simple print (BIOS)
call simple_print

; ****************** Load stage 2 ******************

mov si, Stage2Msg				; Print loading stage 2 message
call simple_print

mov ax, 1						; Start from LBA sector 1
mov ebx, 0x7E00					; Load to offset 0x7E00
mov cx, 7						; Load 7 sectors
call read_sectors

jc err							; Catch any error

mov si, DoneMsg
call simple_print				; Display done message

jmp 0x0000:0x7E00				; Jump to stage 2

err:
mov si, ErrMsg
call simple_print

halt:
hlt
jmp halt

;Data

LoadingMsg		db 0x0D, 0x0A, 'Loading echidnaOS...', 0x0D, 0x0A, 0x0A, 0x00
Stage2Msg		db 'Loading Stage 2...', 0x00
A20Msg			db 'Enabling A20 line...', 0x00
UnrealMsg		db 'Entering Unreal Mode...', 0x00
KernelMsg		db 'Loading kernel...', 0x00
WaitMsg			db 'Waiting for BIOS to stop drives...', 0x00
ErrMsg			db 0x0D, 0x0A, 'Error, system halted.', 0x00
DoneMsg			db '  DONE', 0x0D, 0x0A, 0x00

;Includes

%include 'bootloader/functions/simple_print.inc'
%include 'bootloader/functions/disk.inc'

times 510-($-$$)			db 0x00				; Fill rest with 0x00
bios_signature				dw 0xAA55			; BIOS signature

; ************************* STAGE 2 ************************

mov word [0x0070], timer_int		; Hook the timer interrupt
mov word [0x0072], 0x0000

; ***** A20 *****

mov si, A20Msg					; Display A20 message
call simple_print

call enable_a20					; Enable the A20 address line to access the full memory
jc err							; If it fails, print an error and halt

mov si, DoneMsg
call simple_print				; Display done message

; ***** Unreal Mode *****

mov si, UnrealMsg				; Display unreal message
call simple_print

lgdt [GDT]						; Load the GDT

%include 'bootloader/functions/enter_unreal.inc'		; Enter Unreal Mode

mov si, DoneMsg
call simple_print				; Display done message

; ***** Kernel *****

mov si, KernelMsg				; Show loading kernel message
call simple_print

; Load the kernel to 0x100000

mov si, kernel_name
mov ebx, 0x100000				; Load to offset 0x100000
call load_file

jc err							; Catch any error

mov si, DoneMsg
call simple_print				; Display done message

; *** Wait for drives to be stopped by BIOS ***

mov si, WaitMsg					; Show wait message
call simple_print

mov ecx, 50
call sleep

mov si, DoneMsg
call simple_print				; Display done message

; Done!

%include 'bootloader/functions/enter_pmode.inc'		; Enter Protected Mode

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

;Data

kernel_name		db 'KERNEL  SYS'

;Includes

bits 16

%include 'bootloader/functions/sleep.inc'
%include 'bootloader/functions/timer_int.inc'
%include 'bootloader/functions/fat12.inc'
%include 'bootloader/functions/a20_enabler.inc'
%include 'bootloader/functions/gdt.inc'

times 4096-($-$$)			db 0x00				; Padding
