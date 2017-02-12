#include "../ata.h"

ata_device init_ata_device(uint16_t port_base, uint8_t master) {
    ata_device dev;
    
    dev.data_port = port_base;
    dev.error_port = port_base + 0x01;
    dev.sector_count_port = port_base + 0x02;
    dev.lba_low_port = port_base + 0x03;
    dev.lba_mid_port = port_base + 0x04;
    dev.lba_hi_port = port_base + 0x05;
    dev.device_port = port_base + 0x06;
    dev.command_port = port_base + 0x07;
    dev.control_port = port_base + 0x206;
    dev.master = master;
    
    dev.bytes_per_sector = 512;
    
    return dev;
}

void ata_identify(ata_device dev) {

    port_out_b(dev.device_port, dev.master ? 0xA0 : 0xB0);
    //port_out_b(dev.control_port, 0);
    
    uint8_t status = port_in_b(dev.command_port);
    if (status == 0xFF) {
        text_putstring("No device found! A ");
        return;
    }
        
    port_out_b(dev.sector_count_port, 0);
    port_out_b(dev.lba_low_port, 0);
    port_out_b(dev.lba_mid_port, 0);
    port_out_b(dev.lba_hi_port, 0);
    
    port_out_b(dev.command_port, 0xEC); // identify command

    status = port_in_b(dev.command_port);
    
    if (status == 0x00) {
        text_putstring("No device found! B");
        return;
    }
    
    while (((status & 0x80) == 0x80)
        && ((status & 0x01) != 0x01)) 
        status = port_in_b(dev.command_port);
    
    if (status & 0x01) {
        text_putstring("Error occured!");
        return;
    }
    
    for (uint16_t i = 0; i < 256; i++) {
        uint16_t data = port_in_b(dev.data_port);
        char* foo = "  \0";
        foo[1] = (data >> 8) & 0x00FF;
        foo[0] = data & 0x00FF;
        text_putstring(foo);
        
    }
}
