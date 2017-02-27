#include "keyboard.h"

void keyboard_handler(uint8_t input_byte) {
	asm("xchg bx, bx");
	// something
}
