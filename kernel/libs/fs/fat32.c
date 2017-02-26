#include "fat32.h"

void print_fat_oem(partition partition, ata_device dev) {
    uint8_t* sector = ata_read28(dev, partition.start_lba);
    uint8_t loop;
    for(loop = 0; loop < 8; loop++) {
        text_putchar(mem_load_b(sector+0x3+loop));
        
    }
}

fat32_filesystem get_fs(partition partition, ata_device dev) {
    fat32_filesystem fs;
    
    uint8_t* sector = ata_read28(dev, partition.start_lba);
    uint8_t loop;
    
    for(loop = 0; loop < 8; loop++) {
        fs.oem_name[loop] = mem_load_b(sector+0x3+loop);
    }
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
    }
    for(loop = 0; loop < 8; loop++) {
        fs.fat_name[loop] = mem_load_b(sector+0x52+loop);
    }
    
    // sector_fs_information loading
    
    sector = ata_read28(dev, fs.sector_fs_information);
    
    fs.info_sector.first_signature = mem_load_d(sector);
    fs.info_sector.signature_fs_info = mem_load_d(sector + 0x1E4);
    fs.info_sector.free_clusters = mem_load_d(sector + 0x1E8);
    fs.info_sector.most_recent_cluster = mem_load_d(sector + 0x1EC);
    
    return fs;
}