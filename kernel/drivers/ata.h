#ifndef ATA_H
#define ATA_H

#include <stdint.h>
#include <stddef.h>
#include "system.h"
#include "textdrv.h"

typedef struct ata_device ata_device;

struct ata_device {
    uint8_t master; // this is a boolean
    
    uint16_t data_port;
    uint16_t error_port;
    uint16_t sector_count_port;
    uint16_t lba_low_port;
    uint16_t lba_mid_port;
    uint16_t lba_hi_port;
    uint16_t device_port;
    uint16_t command_port;
    uint16_t control_port;
    
    uint8_t exists;
    
    uint16_t bytes_per_sector;
};

ata_device* get_ata_devices();

ata_device init_ata_device(uint16_t port_base, uint8_t master);
ata_device ata_identify(ata_device dev);
uint8_t* ata_read28(ata_device dev, uint32_t sector);
void ata_write28(ata_device dev, uint32_t sector, uint8_t* data);
#endif
