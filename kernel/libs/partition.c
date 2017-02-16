#include "partition.h"

partition get_partition(uint8_t id, ata_device dev) {
    partition partition;
    
    if (dev.exists == 0) return partition;
    
    if (id > 3) return partition;
    
    uint16_t addr = 446 + id * 16;
    
    uint8_t* sector = ata_read28(dev, 0);

    // ----------------
    
    partition.status = sector[addr];
    partition.type = sector[addr + 4];
    partition.start_lba = (sector[addr + 8 + 3] >> 24) | (sector[addr + 8 + 2] >> 16) | (sector[addr + 8 + 1] >> 8) | sector[addr + 8];
    partition.sector_count = (sector[addr + 12 + 3] >> 24) | (sector[addr + 12 + 2] >> 16) | (sector[addr + 12 + 1] >> 8) | sector[addr + 12];
    partition.exists = 1;
    
    return partition;
}