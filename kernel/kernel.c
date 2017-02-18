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

	text_clear();        
        enumerate_partitions(devices[0]);
        
	text_putstring("\nSoft halting system.");
	system_soft_halt();

}
