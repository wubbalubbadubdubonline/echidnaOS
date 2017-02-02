sleep:

; IN: ECX: Number of ticks of inactivity

test ecx, ecx
jz .quick_exit

push ecx

add ecx, dword [ClockTicks]		; Find target tick

.loop:

cmp dword [ClockTicks], ecx
je .done
jmp .loop

.done:

pop ecx

.quick_exit:
ret
