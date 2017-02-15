#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "../libs/stdint.h"
#include "../libs/stddef.h"

void system_halt(void);
void port_out_b(uint16_t port, uint8_t value);
void port_out_w(uint16_t port, uint16_t value);
void port_out_d(uint16_t port, uint32_t value);
uint8_t port_in_b(uint16_t port);
uint16_t port_in_w(uint16_t port);
uint32_t port_in_d(uint16_t port);

#endif
