#include "partition.h"
#include "../drivers/system.h"

partition get_partition(uint8_t id, ata_device dev) {
    partition partition;
    
    if (dev.exists == 0) return partition;
    
    if (id > 3) return partition;
    
    uint16_t addr = 446 + id * 16;
    
    uint8_t* sector = ata_read28(dev, 0);

    // validity check
    if (sector[510] == 0x55 && sector[511] == 0xAA) {
    } else {
        text_putstring("Drive not bootable!");
        return partition;
    }  
    
    // ----------------
    
    partition.status = sector[addr];
    partition.type = sector[addr + 4];
    partition.start_lba = mem_load_d(sector + addr + 8);
    partition.sector_count = mem_load_d(sector + addr + 0xC);
    partition.exists = 1;
    
    return partition;
}