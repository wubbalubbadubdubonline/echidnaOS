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
	asm("xchg bx,bx");
	build_idt(0x80000, 0x81);
	load_idt(0x80000);
	text_putstring(" Done.\n");

	ata_device* devices = get_ata_devices();

        partition part = get_partition(0, devices[0]);
        
        char buf[9] = {0};
        text_putstring("Partition type: ");
        itoa(part.type, buf, 16);
        text_putstring(buf);
        text_putchar('\n');
        
        text_putstring("First sector: ");
        itoa(part.start_lba, buf, 10);
        text_putstring(buf);
        text_putchar('\n');
        
        text_putstring("Sector count: ");
        itoa(part.sector_count, buf, 10);
        text_putstring(buf);
        text_putchar('\n');
        
	text_putstring("\nHalting system.");
	system_halt();

}
