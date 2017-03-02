#include "ramdrive.h"

uint8_t buf[512];

void ram_write28(uint32_t lba, uint8_t* sector) {
    if (lba > 16384) panic("Ram device LBA out of range(above 8 MiB)");
    printf("Writing a sector to ramdrive at LBA %d!\n", lba);
    uint8_t* addr = (uint8_t*)0xD0000000;
    for (int i = 0; i < 512; i++) {
        addr[lba * 512 + i] = sector[i];
    }
}

uint8_t* ram_read28(uint32_t lba) {
    if (lba > 16384) panic("Ram device LBA out of range(above 8 MiB)");
    printf("Reading a sector from ramdrive at LBA %d!\n", lba);
    uint8_t* addr = (uint8_t*)0xD0000000;
    for (int i = 0; i < 512; i++) {
        buf[i] = addr[lba * 512 + i];
    }
    
    return buf;
}