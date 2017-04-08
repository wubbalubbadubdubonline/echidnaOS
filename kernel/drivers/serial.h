#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>
#include <stddef.h>
#include "system.h"
#include <string.h>

#define COM1 0x3F8
#define COM2 0x2F8
#define COM3 0x3E8
#define COM4 0x2E8

void init_serial_port(uint16_t port);
void send_byte(uint8_t byte, uint16_t port);
uint8_t read_byte(uint16_t port);
void write_string_serial(char* string, uint16_t port);


#endif