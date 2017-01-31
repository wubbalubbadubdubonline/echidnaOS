/* stub kernel that halts the system */

//#include <stdint.h>

asm(".org 0x100000");				// the kernel is loaded at 0x100000

int pos;

void main(void) {
	//asm("xchg bx, bx");
	char* vidmem = (char*) 0xb8000;
	//while (pos < 80 * 25) {
//		vidmem[pos * 2] = 'A';
		// vidmem[pos * 2 + 1] = 0x0F;
		// pos ++;
	// }
	vidmem[0] = 'A';
	vidmem[1] = 0x0F;

	asm("hlt");
}
