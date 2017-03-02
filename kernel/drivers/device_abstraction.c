#include "device_abstraction.h"

ata_device ata_devices[4];

void devices_initalize() {
    ata_device* devs = get_ata_devices();
    ata_devices[0] = devs[0];
    ata_devices[1] = devs[1];
    ata_devices[2] = devs[2];
    ata_devices[3] = devs[3];
    
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
            memcpy((uint8_t*)(mem_location + sector_counter * 512), ata_read28(ata_devices[dev_id], lba_start + 512 * sector_counter), 512);
            
        }
    }
    
    // are we accessing ram device(8mib max, kernel panic otherwise)
    if (strncmp("ram", device_name, 3) == 0) {
        for (uint32_t sector_counter = 0; sector_counter < sector_count; sector_counter++) {
            memcpy((uint8_t*)(mem_location + sector_counter * 512), ram_read28(lba_start + 512 * sector_counter), 512);
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
            ata_write28(ata_devices[dev_id], lba_start + 512 * sector_counter, (uint8_t*)(mem_location + sector_counter * 512));
        }
    }
    
    // are we accessing ram device(8mib max, kernel panic otherwise)
    if (strncmp("ram", device_name, 3) == 0) {
        for (uint32_t sector_counter = 0; sector_counter < sector_count; sector_counter++) {
            ram_write28(lba_start + 512 * sector_counter, (uint8_t*)(mem_location + sector_counter * 512));
        }
    }
}