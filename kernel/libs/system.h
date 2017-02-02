#ifndef __SYSTEM_H__
#define __SYSTEM_H__



#define magic_breakpoint()		asm("xchg bx, bx");

void system_halt(void);
void port_out_b(int port, int value);
void port_out_w(int port, int value);
void port_out_d(int port, int value);
int port_in_b(int port);
int port_in_w(int port);
int port_in_d(int port);




#endif
