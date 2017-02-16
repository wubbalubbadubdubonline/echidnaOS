#ifndef PARTITION_H
#define PARTITION_H

#include "../drivers/ata.h"

typedef struct partition partition;

struct partition {
    uint8_t status;
    uint8_t type;
    uint32_t start_lba;
    uint32_t sector_count;
    
    uint8_t exists;
};

partition get_partition(uint8_t id, ata_device dev);

#endif