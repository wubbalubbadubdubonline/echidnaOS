#include "keyboard.h"

static uint8_t capslock_active = 0;
static char keyboard_buffer[256];
static uint16_t buffer_index;
static char last_char;

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
        if (input_byte == SC_CAPSLOCK || input_byte == SC_LEFT_SHIFT || input_byte == SC_RIGHT_SHIFT || input_byte == SC_LEFT_SHIFT_REL || input_byte == SC_RIGHT_SHIFT_REL) {
                capslock_active = !capslock_active;
		} else if (input_byte < SC_MAX) {
            if (input_byte == SC_ENTER) {
                if (buffer_index < 256) {
                    keyboard_buffer[buffer_index] = '\n';
                    buffer_index++;
                    last_char = '\n';
                }
                
            } else if (input_byte == SC_BACKSPACE) {
                if (buffer_index < 256) {
                    if (buffer_index > 0) {
                        keyboard_buffer[buffer_index] = '\0';
                        buffer_index--;
                        last_char = '\b';
                    }
                }
                
            } else {
                char c = sc_ascii[input_byte];
                if (capslock_active == 0) {
                    c |= 0x20;
                }
                
                if (buffer_index < 256) {
                    keyboard_buffer[buffer_index] = c;
                    buffer_index++;
                    last_char = c;
                }
            }
        }
}

char* get_keyboard_buffer() {
    return keyboard_buffer;
}

void clear_keyboard_buffer() {
    memset(keyboard_buffer, 0, 256);
    buffer_index = 0;
}

char get_last_char() {
    return last_char;
}

void clear_last_char() {
    last_char = 0;
    
}
