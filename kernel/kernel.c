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

	char buf[17];
	int block;

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

		text_putstring("\nDetected memory blocks:\n");

		for (block=0; block<6; block++) {
			text_putstring("Block ");
			text_putstring(itoa(block, buf, 16));
			#if defined(__32BIT__)
			text_putstring("\nBase: ");
			text_putstring(itoa(mem_get_block_base(block), buf, 16));
			text_putstring("\nSize: ");
        	text_putstring(itoa(mem_get_block_size(block), buf, 16));
			#elif defined(__64BIT__)
			text_putstring("\nBase: ");
			text_putstring(ltoa(mem_get_block_base(block), buf, 16));
			text_putstring("\nSize: ");
        	text_putstring(ltoa(mem_get_block_size(block), buf, 16));
			#endif
			text_putstring("\nType: ");
        	text_putstring(itoa(mem_get_block_type(block), buf, 16));
			text_putstring("\nExt: ");
        	text_putstring(itoa(mem_get_block_ext(block), buf, 16));
			text_putchar('\n');
		}

	system_halt();

}
