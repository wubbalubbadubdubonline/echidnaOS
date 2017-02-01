/* stub kernel */

#include "libs/stdint.h"
#include "libs/string.h"

void putchar(char c, char x, char y);
void putstr(char* c, char x, char y);

void _start(void) {
	// asm("xchg bx, bx");
	putstr("Testy test", 5, 4, 10);
	asm("hlt");
}

void putstr(const char* str, char x, char y, int len) {
	//int len = strlen(str);
	int i = 0;
	while (i < len) {
		putchar(str[i], x, y);
		x++;
		if (x > 80 - 1) {
			x = 0;
			y++;
		}
		i++;
	}
}

void putchar(char c, char x, char y) {
	char* vidmem = (char*) 0xb8000;
	short pos = x + 80 * y; // position on 1D array
	vidmem[pos * 2] = c; // video memor
	vidmem[pos * 2 + 1] = 0x0F;
}
