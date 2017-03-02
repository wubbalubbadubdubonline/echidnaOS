#ifndef DEVICE_ABSTRACTION_H
#define DEVICE_ABSTRACTION_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "ata.h"
#include "../libs/panic.h"

/*
 
 Scrap this \/ \/ \/ \/ \/ \/ \/ now it is ata_ where _ is device id
 Device ids:
    0 - ATA
 
 
 ATA format:
    0000     1111
    ^^^^     ^^^^
    ATA ID   Device ID
             (Prim Mas, Prim Sla, Sec Mas, Sec Sla) 
 */

void devices_initalize();

uint8_t* abstraction_read_sector(uint8_t dev, uint32_t lba);
void abstraction_write_sector(uint8_t dev, uint32_t lba, uint8_t* sector);
uint8_t abstraction_device_exists(uint8_t dev);

void disk_load_sector(char* device_name, uint32_t lba_start, uint32_t sector_count, uint32_t mem_location);
void disk_write_sector(char* device_name, uint32_t lba_start, uint32_t sector_count, uint32_t mem_location);


#endif
