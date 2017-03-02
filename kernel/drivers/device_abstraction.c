#include "device_abstraction.h"

ata_device ata_devices[4];

void devices_initalize() {
    ata_device* devs = get_ata_devices();
    ata_devices[0] = devs[0];
    ata_devices[1] = devs[1];
    ata_devices[2] = devs[2];
    ata_devices[3] = devs[3];
    
}

/* old functions, kept until i finish the new functions */
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

/*new abstraction(hopefully better)*/

void disk_load_sector(char* device_name, uint32_t lba_start, uint32_t sector_count, uint32_t mem_location) {
    // are we accessing an ata device
    if (strncmp("ata", device_name, 3) == 0) {
        device_name += 3;
        uint8_t dev_id = atoi(device_name) - 1;
        if (dev_id > 3) panic("ATA id out of range(range is 1 to 4 inclusive)");
        if (ata_devices[dev_id].exists == 0) panic("Device doesn't exist");
        for (uint32_t sector_counter = 0; sector_counter < sector_count; sector_counter++) {
            memcpy((uint8_t*)mem_location, ata_read28(ata_devices[dev_id], lba_start + 512 * sector_counter), 512);
            
        }
    }
}

void disk_write_sector(char* device_name, uint32_t lba_start, uint32_t sector_count, uint32_t mem_location) {
    // are we accessing an ata device
    if (strncmp("ata", device_name, 3) == 0) {
        device_name += 3;
        uint8_t dev_id = atoi(device_name) - 1;
        if (dev_id > 3) panic("ATA id out of range(range is 1 to 4 inclusive)");
        if (ata_devices[dev_id].exists == 0) panic("Device doesn't exist");
        for (uint32_t sector_counter = 0; sector_counter < sector_count; sector_counter++) {
            ata_write28(ata_devices[dev_id], lba_start + 512 * sector_counter, (uint8_t*)mem_location + 512 * sector_counter);
        }
    }
}