#include "keyboard.h"

static uint8_t capslock_active = 0;
static char keyboard_buffer[256];
static uint16_t buffer_index;


const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

void keyboard_handler(uint8_t input_byte) {
	asm("xchg bx, bx");
	// something
        if (input_byte == SC_CAPSLOCK) {
                capslock_active = !capslock_active;
        } else if (input_byte < SC_MAX) {
            if (input_byte == SC_ENTER) {
                if (buffer_index < 256) {
                    keyboard_buffer[buffer_index] = '\n';
                    buffer_index++;
                }
            } else if (input_byte == SC_BACKSPACE) {
                if (buffer_index < 256) {
                    keyboard_buffer[buffer_index] = '\0';
                    buffer_index--;
                }
            } else {
                char c = sc_ascii[input_byte];
                if (capslock_active == 0) {
                    c |= 0x20;
                }
                
                if (buffer_index < 256) {
                    keyboard_buffer[buffer_index] = c;
                    buffer_index++;
                }
            }
        }
}

char* get_keyboard_buffer() {
    return keyboard_buffer;
}

void clear_keyboard_buffer() {
    memset(keyboard_buffer, 0, 256);
}
