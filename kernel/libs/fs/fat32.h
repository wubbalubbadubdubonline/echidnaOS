#ifndef FAT32_FS_H
#define FAT32_FS_H

#include "../stdint.h"
#include "../stddef.h"
#include "../string.h"
#include "../partition.h"
#include "../../drivers/textdrv.h"
#include "../../drivers/system.h" 
#include "../../drivers/device_abstraction.h" 

typedef struct fat32_fs_information_sector {
    uint32_t first_signature;
    uint32_t signature_fs_info;
    uint32_t free_clusters; // -1 if unknown (0xFFFFFFFF)
    uint32_t most_recent_cluster;
    
} fat32_fs_information_sector;

typedef struct fat32_fs_data {
    uint32_t current_dir_cluster;
    uint32_t fat_sector;
    uint32_t root_dir_sector;
    uint32_t cluster_begin_sector;
} fat32_fs_data;


typedef struct fat32_filesystem {
    partition partition;
    char oem_name[9];
    uint8_t exists;
    uint16_t bytes_per_sector;
    uint16_t sectors_per_cluster;
    uint8_t reserved_sectors;
    uint8_t fat_copies;
    uint8_t media_descriptor;
    uint16_t sectors_per_track;
    uint16_t number_of_heads;
    uint32_t hidden_sectors;
    uint32_t sectors;
    uint32_t sectors_per_fat;
    uint16_t flags;
    uint16_t version;
    uint32_t cluster_of_start_root_dir;
    uint16_t sector_fs_information;
    uint16_t sector_fs_backupboot;
    uint8_t logical_drive;
    uint8_t extended_signature;
    uint32_t serial_number;
    uint8_t volume_name[12];
    uint8_t fat_name[9];
    fat32_fs_information_sector info;
    fat32_fs_data data;
} fat32_filesystem;

void print_fat_oem(partition partition, uint8_t dev);
fat32_filesystem get_fs(partition partition, uint8_t dev);

#endif