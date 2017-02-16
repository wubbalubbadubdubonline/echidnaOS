#include "libs/stddef.h"
#include "libs/stdint.h"
#include "libs/string.h"
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

	text_putstring("\nHalting system.");
	system_halt();

}
