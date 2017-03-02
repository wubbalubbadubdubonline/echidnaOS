#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdint.h>
#include <stddef.h>
#include "../drivers/system.h"

void memory_map(uint32_t directory_number, uint32_t phys_address, uint32_t virt_address, uint8_t access);

#endif
