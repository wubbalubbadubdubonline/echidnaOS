#ifndef RAM_DEVICE_H
#define RAM_DEVICE_H

#include <stdio.h>
#include "../libs/panic.h"

void ram_write28(uint32_t lba, uint8_t* sector);
uint8_t* ram_read28(uint32_t lba);

#endif
