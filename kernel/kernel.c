#include "libs/stddef.h"
#include "libs/stdint.h"
#include "libs/string.h"
#include "libs/stdlib.h"
#include "libs/partition.h"
#include "drivers/system.h"
#include "drivers/textdrv.h"
#include "drivers/ata.h"
#include "drivers/pic.h"
#include "drivers/gdt.h"
#include "drivers/idt.h"

void _start(void) {

	char buf[16] = {0};

	text_clear();

	text_putstring("echidnaOS\n\n");

	text_putstring(itoa(mem_load_d(0x7DF5)+mem_load_d(0x7DF9), buf, 10));
	text_putstring(" bytes of usable extended memory detected.\n\n");

	text_putstring("Initialising PIC...");

	map_PIC(0x20, 0x28);	// map the PIC0 at int 0x20-0x27 and PIC1 at 0x28-0x2F

	text_putstring(" Done.\n");

	text_putstring("Building descriptor tables...");

	create_GDT();		// build the GDT
	create_IDT();		// build the IDT

	load_segments();	// activate the GDT
	enable_ints();		// activate the IDT

	text_putstring(" Done.\n");

	ata_device* devices = get_ata_devices();

        partition_table table; table = enumerate_partitions(devices[0]);
        
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
