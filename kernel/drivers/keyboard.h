#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "textdrv.h"
#include "../libs/panic.h"

#define SC_MAX 0x57
#define SC_CAPSLOCK 0x3A
#define SC_ENTER 0x1C
#define SC_BACKSPACE 0x0E
#define SC_RIGHT_SHIFT 0x36
#define SC_LEFT_SHIFT 0x2A
#define SC_RIGHT_SHIFT_REL 0xB6
#define SC_LEFT_SHIFT_REL 0xAA

void keyboard_handler(uint8_t input_byte);

char keyboard_fetch_char(void);
char keyboard_getchar(void);
void keyboard_getstring(char* string, uint32_t limit);

#endif
