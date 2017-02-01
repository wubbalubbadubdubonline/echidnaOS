/* stub kernel */

#include "libs/stdint.h"
// #include "libs/string.h"

void putchar(char c, char x, char y);
void putstr(const char* str, char x, char y, int len);

void _start(void) {
	//asm("xchg bx, bx");

	putchar('T', 5, 5);
	putchar('e', 6, 5);
	putchar('s', 7, 5);
	putchar('t', 8, 5);
	putchar('y', 9, 5);
	putchar(' ', 10, 5);
	putchar('t', 11, 5);
	putchar('e', 12, 5);
	putchar('s', 13, 5);
	putchar('t', 14, 5);

	putstr("Testy test", 5, 4, 10);

	//asm("hlt");
}

void putstr(const char* str, char x, char y, int len) {
	int i = 0;
	putchar('I', x, y);
	// int len = strlen(str);
	// putchar('L', x, y);
	int pos = x + 80 * y;
	putchar('P', x, y);
	char* vidmem = (char*) 0xb8000;
	putchar('V', x, y);
	for ( ; i < len; i++) {
		vidmem[pos * 2] = str[i];
		vidmem[pos * 2 + 1] = 0x0F;
		pos++;
	}
}

void putchar(char c, char x, char y) {
	char* vidmem = (char*) 0xb8000;
	short pos = x + 80 * y; // position on 1D array
	vidmem[pos * 2] = c; // video memor
	vidmem[pos * 2 + 1] = 0x0F;
}
