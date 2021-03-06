read_sector:

; *************************************************
;     Reads a floppy sector with an LBA address
; *************************************************

; IN:
; AX = LBA sector to load
; DL = Drive number
; ES = Buffer segment
; BX = Buffer offset

; OUT:
; Carry if error

push ax									; Save all GPRs
push bx									; Prepare entering routine
push cx
push dx

push dx									; Save drive number in stack

; LBA to CHS

xor dx, dx								; XOR DX for division
div word [bpbSectorsPerTrack]			; Divide LBA / Sectors per track
inc dl									; Adjust for sector 0
mov byte [.absolute_sector], dl			; Save sector
xor dx, dx								; XOR DX for division
div word [bpbHeadsPerCylinder]			; Divide / Number of heads
mov byte [.absolute_head], dl			; Save head
mov byte [.absolute_track], al			; Save track

pop dx									; Restore drive number from stack

; Prepare registers for BIOS int 0x13

mov ah, 0x02							; Read sector function
mov al, 1								; Read 1 sector
mov ch, byte [.absolute_track]			; Use data we calculated
mov cl, byte [.absolute_sector]
mov dh, byte [.absolute_head]

clc										; Clear carry for int 0x13 because some BIOSes may not clear it on success

int 0x13								; Call int 0x13

.done:

pop dx									; Restore all GPRs
pop cx
pop bx
pop ax
ret										; Exit routine


.absolute_sector		db 0x00
.absolute_head			db 0x00
.absolute_track			db 0x00


read_sectors:

; **********************************************************
;     Reads multiple LBA addressed sectors from a floppy
; **********************************************************

; IN:
; AX = LBA starting sector
; DL = Drive number
; ES = Buffer segment
; EBX = Buffer offset
; CX = Sectors count

; OUT:
; Carry if error

push eax									; Save GPRs
push ebx
push ecx
push edx
push esi
push edi

.loop:

push es
push ebx

mov bx, 0x7000							; Load in a temp buffer
mov es, bx
xor bx, bx

call read_sector						; Read sector

pop ebx
pop es

jc .done								; If carry exit with flag

push ds

mov si, 0x7000
mov ds, si
mov edi, ebx
xor esi, esi

push ecx
mov ecx, 512
a32 o32 rep movsb
pop ecx

pop ds

inc ax									; Increment sector
add ebx, 512							; Add 512 to the buffer

loop .loop								; Loop!

.done:
pop edi
pop esi
pop edx
pop ecx									; Restore GPRs
pop ebx
pop eax
ret										; Exit routine
