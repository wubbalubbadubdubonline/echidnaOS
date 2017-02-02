#ifndef __SYSTEM_H__
#define __SYSTEM_H__



#define magic_breakpoint()		asm("xchg bx, bx");

void system_halt(void);	




#endif
