#ifndef PARTITION_H
#define PARTITION_H

#include "../drivers/ata.h"
#include "../drivers/device_abstraction.h"

typedef struct partition partition;
typedef struct partition_table partition_table;
typedef struct extended_partition extended_partition;

struct partition {
    uint8_t status;
    uint8_t type;
    uint32_t start_lba;
    uint32_t sector_count;
    
    uint8_t exists;
};

struct extended_partition {
    uint8_t status;
    uint8_t type;
    uint32_t start_lba;
    uint32_t sector_count;
    
    partition partitions[2];
    
    uint8_t exists;
};

struct partition_table {
    partition partitions[8];
};

partition get_partition(uint8_t id, char* dev);
extended_partition get_extended_partition(partition partition, char* dev);
partition_table enumerate_partitions(char* dev);

#endif