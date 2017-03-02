#ifndef DEVICE_ABSTRACTION_H
#define DEVICE_ABSTRACTION_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

// individual device drivers
#include "ata.h"
#include "ramdrive.h"

// panic
#include "../libs/panic.h"

void devices_initalize();

void disk_load_sector(char* device_name, uint32_t lba_start, uint32_t sector_count, uint32_t mem_location);
void disk_write_sector(char* device_name, uint32_t lba_start, uint32_t sector_count, uint32_t mem_location);


#endif
