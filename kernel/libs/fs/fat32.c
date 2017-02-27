#include "fat32.h"

uint32_t cluster_to_lba(fat32_filesystem fs, uint32_t cluster){
	return fs.data.cluster_begin_sector+(fs.sectors_per_cluster * (cluster-2));
}

void print_fat_oem(partition partition, ata_device dev) {
    uint8_t* sector = ata_read28(dev, partition.start_lba);
    uint8_t loop;
    for(loop = 0; loop < 8; loop++) {
        text_putchar(mem_load_b(sector+0x3+loop));
        
    }
}

fat32_filesystem get_fs(partition partition, ata_device dev) {
    fat32_filesystem fs;
    
//     if (dev.exists == 0) return fs;
//     if (partition.type != 0xC) return fs;
    
    uint8_t* sector = ata_read28(dev, partition.start_lba);
    uint8_t loop;

    fs.partition = partition;
    
    for(loop = 0; loop < 8; loop++) {
        fs.oem_name[loop] = mem_load_b(sector+0x3+loop);
    } fs.oem_name[8] = 0x0;
    
    fs.bytes_per_sector = mem_load_w(sector+0xB);
    fs.sectors_per_cluster = mem_load_b(sector+0xD);
    fs.reserved_sectors = mem_load_w(sector+0xE);
    fs.fat_copies = mem_load_b(sector+0x10);
    fs.media_descriptor = mem_load_b(sector+0x15);
    fs.sectors_per_track = mem_load_w(sector+0x18);
    fs.number_of_heads = mem_load_w(sector+0x1A);
    fs.hidden_sectors = mem_load_d(sector+0x1C);
    fs.sectors = mem_load_d(sector+0x20);
    fs.sectors_per_fat = mem_load_d(sector+0x24);
    fs.flags = mem_load_w(sector+0x28);
    fs.version = mem_load_w(sector+0x2A);
    fs.cluster_of_start_root_dir = mem_load_d(sector+0x2C);
    fs.sector_fs_information = mem_load_w(sector+0x30);
    fs.sector_fs_backupboot = mem_load_w(sector+0x32);
    fs.logical_drive = mem_load_b(sector+0x40);
    fs.extended_signature = mem_load_b(sector+0x42);
    fs.serial_number = mem_load_d(sector+0x43);
    for(loop = 0; loop < 11; loop++) {
        fs.volume_name[loop] = mem_load_b(sector+0x47+loop);
    } fs.volume_name[11] = 0x0;
    for(loop = 0; loop < 8; loop++) {
        fs.fat_name[loop] = mem_load_b(sector+0x52+loop);
    } fs.fat_name[8] = 0x0;
    
//     if (strcmp("FAT32   ", fs.fat_name) != 0) return fs;
    
    // sector_fs_information loading
    
    sector = ata_read28(dev, fs.sector_fs_information);
    
    fs.info.first_signature = mem_load_d(sector);
    fs.info.signature_fs_info = mem_load_d(sector + 0x1E4);
    fs.info.free_clusters = mem_load_d(sector + 0x1E8);
    fs.info.most_recent_cluster = mem_load_d(sector + 0x1EC);
    
    fs.data.cluster_begin_sector = fs.partition.start_lba + fs.reserved_sectors + (fs.fat_copies * fs.sectors_per_fat);
    fs.data.root_dir_sector = cluster_to_lba(fs, fs.cluster_of_start_root_dir);
    fs.data.fat_sector = fs.partition.start_lba + fs.reserved_sectors;
    fs.data.current_dir_cluster = fs.cluster_of_start_root_dir;
    
    fs.exists = 1;
    
    return fs;
}

void list_directory(uint32_t cluster, fat32_filesystem fs, ata_device dev){
    uint8_t* buf;
    uint32_t ccluster = cluster;
    uint32_t sector = cluster_to_lba(fs, ccluster);
    uint16_t dir_size = 0;
    uint8_t done = 0;
    uint8_t current_col = 0;
    uint8_t current_row = 0;
    uint8_t oypos = 0;
    
    uint8_t i;
    
    while (done == 0) {
        buf = ata_read28(dev, sector);
        
        for (i = 0; i < 16; i++) {
            uint16_t loc = 0x20 * i;
            
        }
    }
    
}

