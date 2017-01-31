#ifndef PORTS_H
#define PORTS_H

#include <stdint.h>

uint32_t port_byte_in (uint32_t port);
void port_byte_out (uint32_t port, uint32_t data);
uint32_t port_word_in (uint32_t port);
void port_word_out (uint32_t port, uint32_t data);
uint32_t port_dword_in (uint32_t port);
void port_dword_out (uint32_t port, uint32_t data);
void insl(uint32_t port, uint32_t addr, uint32_t cnt);

#endif
