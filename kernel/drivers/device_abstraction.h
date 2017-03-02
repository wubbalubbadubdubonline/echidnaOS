#ifndef DEVICE_ABSTRACTION_H
#define DEVICE_ABSTRACTION_H

#include <stdint.h>
#include <stddef.h>
#include "ata.h"

/*
 
 Device ids:
    0 - ATA
 
 
 ATA format:
    0000     1111
    ^^^^     ^^^^
    ATA ID   Device ID
             (Prim Mas, Prim Sla, Sec Mas, Sec Sla) 
 */

void set_ata_devices(ata_device* devs);

uint8_t* abstraction_read_sector(uint8_t dev, uint32_t lba);
void abstraction_write_sector(uint8_t dev, uint32_t lba, uint8_t* sector);
uint8_t abstraction_device_exists(uint8_t dev);

#endif
