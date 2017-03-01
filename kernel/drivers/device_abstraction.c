#include "device_abstraction.h"

ata_device ata_devices[4];

void set_ata_devices(ata_device* devs) {
    ata_devices[0] = devs[0];
    ata_devices[1] = devs[1];
    ata_devices[2] = devs[2];
    ata_devices[3] = devs[3];
    
}

uint8_t* abstraction_read_sector(uint8_t dev, uint32_t lba) {
    switch (dev >> 4 & 0x0F) {
        case 0:
            return ata_read28(ata_devices[dev & 0x0F], lba);
    }
}

void abstraction_write_sector(uint8_t dev, uint32_t lba, uint8_t* sector) {
    switch (dev >> 4 & 0x0F) {
        case 0:
            ata_write28(ata_devices[dev & 0x0F], lba, sector);
            break;
    }
}

uint8_t abstraction_device_exists(uint8_t dev) {
    switch (dev >> 4 & 0x0F) {
        case 0:
            return ata_devices[dev & 0x0F].exists;
    }
}