timer_int:

push ax

xor ax, ax
mov ds, ax

inc dword [ClockTicks]

pop ax

iret

ClockTicks		dd	0x00000000
