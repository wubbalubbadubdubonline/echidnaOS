#include "fat32.h"

uint32_t cluster2lba(fat32_filesystem fs, uint32_t cluster){
	return fs.data.cluster_begin_sector+(fs.sectors_per_cluster * (cluster-2));
}

fat32_filesystem get_fs(partition partition, char* dev) {
    fat32_filesystem fs;
    
    if (partition.type != 0xC)                      return fs;
    
    uint8_t sector[512] = {1};
    disk_load_sector(dev, partition.start_lba, 1, (uint32_t)sector);
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


    if (strcmp("FAT32   ", fs.fat_name) != 0) return fs;
    
    // sector_fs_information loading
    
    
    memset(sector, 0, 512);
    disk_load_sector(dev, fs.sector_fs_information, 1, (uint32_t)sector);
    
    fs.info.first_signature = mem_load_d(sector);
    fs.info.signature_fs_info = mem_load_d(sector + 0x1E4);
    fs.info.free_clusters = mem_load_d(sector + 0x1E8);
    fs.info.most_recent_cluster = mem_load_d(sector + 0x1EC);
    
    fs.data.cluster_begin_sector = fs.partition.start_lba + fs.reserved_sectors + (fs.fat_copies * fs.sectors_per_fat);
    fs.data.root_dir_sector = cluster2lba(fs, fs.cluster_of_start_root_dir);
    fs.data.fat_sector = fs.partition.start_lba + fs.reserved_sectors;
    fs.data.current_dir_cluster = fs.cluster_of_start_root_dir;
    
    fs.exists = 1;
    
    printf("sectors per cluster: %d\n", fs.sectors_per_cluster);

    fat32_directory_entry dirent[16];

    disk_load_sector(dev, fs.data.root_dir_sector, 1, (uint32_t)&dirent[0]);

    for (int counternigger = 0; counternigger < 16; counternigger++) {
        if (dirent[counternigger].name[0] == 0x00) {
            break;
        }

        if ((dirent[counternigger].attributes & 0x0F) == 0x0F)
            continue;

        char foo[] = "        ";
        for (int j = 0; j < 8; j++) {
            foo[j]=dirent[counternigger].name[j];
        }

        printf("%s\n", foo);

        if((dirent[counternigger].attributes & 0x10) == 0x10) {
            continue;
        }

        uint32_t fileCluster = ((uint32_t)dirent[counternigger].firstClusterHi) << 16 | ((uint32_t) dirent[counternigger].firstClusterLo);    
        int32_t size = dirent[counternigger].size;

        uint32_t next_file_cluster = fileCluster;

        uint8_t buffer[512];
        uint8_t fatbuffer[512];

        printf("file size = %d\n", size);

        while (size > 0) {
            uint32_t fileSector = cluster2lba(fs, next_file_cluster);
            uint32_t sectorOffset = 0;

            for (; size > 0; size -= 512) {
        
                disk_load_sector(dev, fileSector + sectorOffset, 1, (uint32_t)buffer);

                buffer[size > 512 ? 512 : size] = '\0';
                printf("%s", buffer);

                if (++sectorOffset > fs.sectors_per_cluster)
                    break;
            }

            uint32_t fat_sector_current_cluster = next_file_cluster / (512 / 4);
            disk_load_sector(dev, fs.data.fat_sector + sectorOffset, 1, (uint32_t)fatbuffer);

            uint32_t fat_offset_sector_current_cluster = next_file_cluster % (512 / 4);

            next_file_cluster = ((uint32_t*)&fatbuffer)[fat_offset_sector_current_cluster] & 0x0FFFFFFF;

            // printf("remaining size = 0x%x\n", size);

        }
    }

    return fs;
}

