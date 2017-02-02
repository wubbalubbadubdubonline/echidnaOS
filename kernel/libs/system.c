#include "system.h"

void system_halt(void) {
	asm volatile ("nop; nop; cli; hlt;");
}

void port_out_b(int port, int value) {
	asm volatile (	"out dx, al;"
					:
					: "d" (port), "a" (value)
					: );
}

void port_out_w(int port, int value) {
	asm volatile (	"out dx, ax;"
					:
					: "d" (port), "a" (value)
					: );
}

void port_out_d(int port, int value) {
	asm volatile (	"out dx, eax;"
					:
					: "d" (port), "a" (value)
					: );
}

int port_in_b(int port) {
	asm volatile (	"xor eax, eax;"
					"in al, dx;"
					:
					: "d" (port)
					: );
}

int port_in_w(int port) {
	asm volatile (	"xor eax, eax;"
					"in ax, dx;"
					:
					: "d" (port)
					: );
}

int port_in_d(int port) {
	asm volatile (	"in eax, dx;"
					:
					: "d" (port)
					: );
}
