#include "partition.h"
#include "../drivers/system.h"
#include <stdlib.h>

static partition_table table;

char* names[] = {"Empty", 
                      "FAT12",
                      "XENIX root",
                      "XENIX usr",
                      "FAT16",
                      "Extended partition CHS",
                      "FAT16B",
                      "IFS/HPFS/NTFS/exFAT/qnx 7",
                      "FAT12/FAT16 logical",
                      "qnz 9",
                      "OS/2 Boot Manager",
                      "FAT32 CHS",
                      "FAT32 LBA",
                      "Reserved",
                      "FAT16B LBA",
                      "Extended partition LBA"
};

partition get_partition(uint8_t id, char* dev) {
    partition partition;
    
    if (id > 3)                                 return partition;
    
    uint16_t addr = 446 + id * 16;
    
    uint8_t sector[512] = {1};
    disk_load_sector(dev, 0, 1, (uint32_t)sector);
    
    // validity check
    if (sector[510] == 0x55 && sector[511] == 0xAA) {
    } else {
        text_putstring("Drive not bootable!\n");
        return partition;
    }  
    
    // ----------------
    
    partition.status = mem_load_b(sector + addr);
    partition.type = mem_load_b(sector + addr + 4);
    partition.start_lba = mem_load_d(sector + addr + 8);
    partition.sector_count = mem_load_d(sector + addr + 0xC);
    partition.exists = 1;
    
    if (partition.type == 0)
        partition.exists = 0;
    
    return partition;
}

partition get_partition_from_sector(uint8_t id, uint8_t* sector) {
    partition partition;
    
    uint16_t addr = 446 + id * 16;
    
    // validity check
    if (sector[510] == 0x55 && sector[511] == 0xAA) {
    } else {
        text_putstring("Drive not bootable!\n");
        return partition;
    }  
    
    // ----------------
    
    partition.status = mem_load_b(sector + addr);
    partition.type = mem_load_b(sector + addr + 4);
    partition.start_lba = mem_load_d(sector + addr + 8);
    partition.sector_count = mem_load_d(sector + addr + 0xC);
    partition.exists = 1;
    
    if (partition.type == 0)
        partition.exists = 0;
    
    return partition;
}

extended_partition get_extended_partition(partition partition, char* dev) {
    extended_partition ext_partition;

    if (partition.exists == 0)                      return ext_partition;    
    if (partition.type != 0xf)                      return ext_partition;

    uint8_t sector[512] = {1};
    disk_load_sector(dev, partition.start_lba, 1, (uint32_t)sector);
    
    ext_partition.status = partition.status;
    ext_partition.type = 0xf;
    ext_partition.start_lba = partition.start_lba;
    ext_partition.sector_count = partition.sector_count;
    ext_partition.exists = 1;

    uint8_t p_id;
    for (p_id = 0; p_id < 2; p_id++) {
        ext_partition.partitions[p_id] = get_partition_from_sector(p_id, sector);
    }
    
    return ext_partition;
}

partition_table enumerate_partitions(char* dev) {
    
    uint8_t table_id = 0;
    uint8_t id = 0;
    
    text_putstring("Enumerating partitions: \n");
    
    char buf[9] = {0};
    
    for (id = 0; id < 4; id++) {
        partition part = get_partition(id, dev);
        
        if (part.exists != 0) {
            
            printf("- %s - %x sectors\n", names[part.type], part.sector_count);
            
            if (part.type == 0xf) {
                extended_partition ext_part = get_extended_partition(part, dev);
                uint8_t id_;
                for (id_ = 0; id_ < 2; id_++) {
                    partition part_ = ext_part.partitions[id_];
                    
                    if (part_.exists != 0) {
                        printf("    - %s - %x sectors\n", names[part_.type], part_.sector_count);
            
                        // ------------------------
                        table.partitions[table_id].status = part_.status;
                        table.partitions[table_id].type = part_.type;
                        table.partitions[table_id].start_lba = part_.start_lba;
                        table.partitions[table_id].sector_count = part_.sector_count;
                        table.partitions[table_id].exists = part_.exists;
                        table_id++;
                    }
                }
                
            } else {
                table.partitions[table_id].status = part.status;
                table.partitions[table_id].type = part.type;
                table.partitions[table_id].start_lba = part.start_lba;
                table.partitions[table_id].sector_count = part.sector_count;
                table.partitions[table_id].exists = part.exists;
                table_id++;
            }
            
        }
        
    }
    
    return table;
}
