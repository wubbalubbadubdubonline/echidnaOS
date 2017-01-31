/* stub kernel that halts the system */

asm(".org 0x100000");				// the kernel is loaded at 0x100000

void main(void) {
	asm("hlt");
}
