
%include 'bootloader/includes/stage1.inc'

; ************************* STAGE 2 ************************

cli

mov word [0x0070], timer_int		; Hook the timer interrupt
mov word [0x0072], 0x0000

sti

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

%include 'bootloader/includes/enter_unreal.inc'		; Enter Unreal Mode

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

; *** Detect memory ***

mov si, MemoryMsg
call simple_print

mov edi, 0x5000					; The memory map is available at 0x00005000
xor ebx, ebx					; Clear EBX
mov edx, 0x534D4150				; Magic number

detect_memory:

mov eax, 0xE820					; BIOS function
mov ecx, 24

clc								; Clear carry

int 0x15						; Detect memory

jc .done

test ebx, ebx					; Check for last entry
jz .done

add edi, 24						; Increment EDI

jmp detect_memory
.done:

mov si, DoneMsg
call simple_print				; Display done message

; *** Wait for drives to be stopped by BIOS ***

mov si, WaitMsg					; Show wait message
call simple_print

mov ecx, 50
call sleep

mov si, DoneMsg
call simple_print				; Display done message

; ***** 80x50 text mode, disable hardware cursor *****

mov ax, 1112h                                   ; Set params
xor bx, bx                                      ; Default font(hopefully exists)
int 10h                                         ; Set mode using a bios interrupt

mov ah, 0x01					; Disable VGA cursor
mov cx, 0x2607
int 0x10

jmp arch_specific

;Data

kernel_name		db 'KERNEL  SYS'
A20Msg			db 'Enabling A20 line...', 0x00
UnrealMsg		db 'Entering Unreal Mode...', 0x00
KernelMsg		db 'Loading kernel...', 0x00
MemoryMsg		db 'Detecting memory...', 0x00
WaitMsg			db 'Waiting for BIOS to stop drives...', 0x00

;Includes

%include 'bootloader/includes/sleep.inc'
%include 'bootloader/includes/timer_int.inc'
%include 'bootloader/includes/fat12.inc'
%include 'bootloader/includes/a20_enabler.inc'
%include 'bootloader/includes/gdt.inc'
