#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include "../libs/stdint.h"
#include "../libs/stddef.h"
#include "../libs/string.h"

#define SC_MAX 0x57
#define SC_CAPSLOCK 0x3A
#define SC_ENTER 0x1C
#define SC_BACKSPACE 0x0E

void keyboard_handler(uint8_t input_byte);

char* get_keyboard_buffer();
void clear_keyboard_buffer();

#endif
