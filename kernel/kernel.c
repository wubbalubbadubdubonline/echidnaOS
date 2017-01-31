/* stub kernel */

void putchar(char c);

void _start(void) {
	asm("xchg bx, bx");
	putchar('a');
	asm("hlt");
}

void putchar(char c) {
	char* vidmem = (char*) 0xb8000;
	vidmem[0] = c;
	vidmem[1] = 0x0F;
}
