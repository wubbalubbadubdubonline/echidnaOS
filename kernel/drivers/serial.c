#include "serial.h"

void init_serial_port(uint16_t port) {
    port_out_b(port + 1, 0x00);
    port_out_b(port + 3, 0x80);
    port_out_b(port + 0, 0x03);
    port_out_b(port + 1, 0x00);
    port_out_b(port + 3, 0x03);
    port_out_b(port + 2, 0xC7);
    port_out_b(port + 4, 0x0B);
}

int serial_received(uint16_t port) {
   return port_in_b(port + 5) & 1;
}
 
uint8_t read_serial(uint16_t port) {
   while (serial_received(port) == 0);
 
   return port_in_b(port);
}

int is_transmit_empty(uint16_t port) {
   return port_in_b(port + 5) & 0x20;
}
 
void write_serial(uint8_t byte, uint16_t port) {
   while (is_transmit_empty(port) == 0);
 
   return port_out_b(port, byte);
}

void write_string_serial(char* string, uint16_t port) {
    int len = strlen(string);
    for(int i = 0; i < len; i++) {
        write_serial(string[i], port);
    }
}