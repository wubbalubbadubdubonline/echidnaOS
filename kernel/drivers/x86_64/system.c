#include "../system.h"

void system_halt(void) {
	asm volatile ("cli; hlt;");
}

void port_out_b(uint16_t port, uint8_t value) {
	asm volatile (	"out dx, al;"
					:
					: "d" (port), "a" (value)
					: );
}

void port_out_w(uint16_t port, uint16_t value) {
	asm volatile (	"out dx, ax;"
					:
					: "d" (port), "a" (value)
					: );
}

void port_out_d(uint16_t port, uint32_t value) {
	asm volatile (	"out dx, eax;"
					:
					: "d" (port), "a" (value)
					: );
}

uint8_t port_in_b(uint16_t port) {
	uint8_t value;
	asm volatile (	"in al, dx;"
					: "=a" (value)
					: "d" (port)
					: );
	return value;
}

uint16_t port_in_w(uint16_t port) {
	uint16_t value;
	asm volatile (	"in ax, dx;"
					: "=a" (value)
					: "d" (port)
					: );
	return value;
}

uint32_t port_in_d(uint16_t port) {
	uint32_t value;
	asm volatile (	"in eax, dx;"
					: "=a" (value)
					: "d" (port)
					: );
	return value;
}
