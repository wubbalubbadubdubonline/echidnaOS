#ifndef ATA_H
#define ATA_H

#include "../libs/stdint.h"
#include "../libs/stddef.h"
#include "system.h"
#include "textdrv.h"

typedef struct ata_device ata_device;

struct ata_device {
    uint8_t master; // this is a boolean
    
    uint16_t data_port;
    uint8_t error_port;
    uint8_t sector_count_port;
    uint8_t lba_low_port;
    uint8_t lba_mid_port;
    uint8_t lba_hi_port;
    uint8_t device_port;
    uint8_t command_port;
    uint8_t control_port;
    
    uint16_t bytes_per_sector;
};

ata_device init_ata_device(uint16_t port_base, uint8_t master);
void ata_identify(ata_device dev);

#endif
