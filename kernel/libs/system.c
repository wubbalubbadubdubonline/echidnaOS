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
	int value;
	asm volatile (	"xor eax, eax;"
					"in al, dx;"
					: "=a" (value)
					: "d" (port)
					: );
	return value;
}

int port_in_w(int port) {
	int value;
	asm volatile (	"xor eax, eax;"
					"in ax, dx;"
					: "=a" (value)
					: "d" (port)
					: );
	return value;
}

int port_in_d(int port) {
	int value;
	asm volatile (	"in eax, dx;"
					: "=a" (value)
					: "d" (port)
					: );
	return value;
}
