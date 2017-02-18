#include "libs/stddef.h"
#include "libs/stdint.h"
#include "libs/string.h"
#include "libs/stdlib.h"
#include "libs/partition.h"
#include "drivers/system.h"
#include "drivers/textdrv.h"
#include "drivers/ata.h"
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

        partition_table table; table = enumerate_partitions(devices[0]);
        
        char buf[9] = {0};
        if (table.partitions[0].exists != 0)
            text_putstring(itoa(table.partitions[0].type, buf, 16));
        if (table.partitions[1].exists != 0)
            text_putstring(itoa(table.partitions[1].type, buf, 16));
        if (table.partitions[2].exists != 0)
            text_putstring(itoa(table.partitions[2].type, buf, 16));
        if (table.partitions[3].exists != 0)
            text_putstring(itoa(table.partitions[3].type, buf, 16));
        if (table.partitions[4].exists != 0)
            text_putstring(itoa(table.partitions[4].type, buf, 16));
        if (table.partitions[5].exists != 0)
            text_putstring(itoa(table.partitions[5].type, buf, 16));
        if (table.partitions[6].exists != 0)
            text_putstring(itoa(table.partitions[6].type, buf, 16));
        if (table.partitions[7].exists != 0)
            text_putstring(itoa(table.partitions[7].type, buf, 16));
        
	text_putstring("\nSoft halting system.");
	system_soft_halt();

}
