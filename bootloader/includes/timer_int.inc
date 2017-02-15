timer_int:

push ax
push ds

xor ax, ax
mov ds, ax

inc dword [ClockTicks]

pop ds
pop ax

iret

ClockTicks		dd	0x00000000
