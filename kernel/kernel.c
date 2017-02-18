#include "libs/stddef.h"
#include "libs/stdint.h"
#include "libs/string.h"
#include "libs/stdlib.h"
#include "libs/partition.h"
#include "drivers/system.h"
#include "drivers/textdrv.h"
#include "drivers/ata.h"
#include "drivers/memory.h"
#include "drivers/paging.h"
#include "drivers/pic.h"
#include "drivers/idt.h"

void _start(void) {

	text_clear();

	text_putstring("echidnaOS\n\n");

	text_putstring("Initialising PIC...");
	map_PIC(0x20, 0x28);
	text_putstring(" Done.\n");

	text_putstring("Building IDT...");

	create_IDT();		// build the IDT

	enable_ints();		// activate the IDT

	text_putstring(" Done.\n");

	ata_device* devices = get_ata_devices();

        partition part = get_partition(0, devices[0]);
        
        char buf[9] = {0};
        text_putstring("Partition type: ");
        itoa(part.type, buf, 16);
        text_putstring(buf);
        text_putchar('\n');

        char bufa[9] = {0};        
        text_putstring("First sector: ");
        itoa(part.start_lba, bufa, 16);
        text_putstring(bufa);
        text_putchar('\n');

        char bufb[9] = {0};
        text_putstring("Sector count: ");
        itoa(part.sector_count, bufb, 16);
        text_putstring(bufb);
        text_putchar('\n');
        
        
        // -----------
        part = get_partition(1, devices[0]);
        
        text_putstring("Partition type: ");
        itoa(part.type, buf, 16);
        text_putstring(buf);
        text_putchar('\n');

        text_putstring("First sector: ");
        itoa(part.start_lba, bufa, 16);
        text_putstring(bufa);
        text_putchar('\n');

        text_putstring("Sector count: ");
        itoa(part.sector_count, bufb, 16);
        text_putstring(bufb);
        text_putchar('\n');
        
        
        // -----------
        part = get_partition(2, devices[0]);
        
        text_putstring("Partition type: ");
        itoa(part.type, buf, 16);
        text_putstring(buf);
        text_putchar('\n');

        text_putstring("First sector: ");
        itoa(part.start_lba, bufa, 16);
        text_putstring(bufa);
        text_putchar('\n');

        text_putstring("Sector count: ");
        itoa(part.sector_count, bufb, 16);
        text_putstring(bufb);
        text_putchar('\n');
        
        
        // -----------
        part = get_partition(3, devices[0]);
        
        text_putstring("Partition type: ");
        itoa(part.type, buf, 16);
        text_putstring(buf);
        text_putchar('\n');

        text_putstring("First sector: ");
        itoa(part.start_lba, bufa, 16);
        text_putstring(bufa);
        text_putchar('\n');

        text_putstring("Sector count: ");
        itoa(part.sector_count, bufb, 16);
        text_putstring(bufb);
        text_putchar('\n');
        
	text_putstring("\nSoft halting system.");
	system_soft_halt();

}
