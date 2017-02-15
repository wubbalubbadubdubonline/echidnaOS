/* stub kernel */

#include "libs/stddef.h"
#include "libs/stdint.h"
#include "libs/string.h"
#include "drivers/system.h"
#include "drivers/textdrv.h"
#include "drivers/ata.h"
#include "drivers/memory.h"
#include "drivers/paging.h"

void _start(void) {

	text_clear();

	text_putchar(0x00);
	text_putstring("echidnaOS\nCrispy with ATA support\n");
        
        ata_device ata0m; ata0m = init_ata_device(0x1F0,1); // Primary master
        text_putstring("ATA primary master: ");
        ata_identify(ata0m);
        text_putchar('\n');
        
        ata_device ata0s; ata0s = init_ata_device(0x1F0,0); // Primary slave
        text_putstring("ATA primary slave: ");
        ata_identify(ata0s);
        text_putchar('\n');
        
        ata_device ata1m; ata1m = init_ata_device(0x170,1); // Secondary master
        text_putstring("ATA secondary master: ");
        ata_identify(ata1m);
        text_putchar('\n');
        
        ata_device ata1s; ata1s = init_ata_device(0x170,0); // Secondary slave
        text_putstring("ATA secondary slave: ");
        ata_identify(ata1s);
        text_putchar('\n');

        ata_write28(ata0m, 1, (uint8_t*)0x7c00, 512);
        ata_flush(ata0m);
        ata_read28(ata0m, 1, 512);

	system_halt();

}
