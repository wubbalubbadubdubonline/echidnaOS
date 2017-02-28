#include "libs/stddef.h"
#include "libs/stdint.h"
#include "libs/string.h"
#include "libs/stdlib.h"
#include "libs/stdarg.h"
#include "libs/stdio.h"
#include "libs/math.h"
#include "libs/partition.h"
#include "libs/ctype.h"
#include "drivers/system.h"
#include "drivers/textdrv.h"
#include "drivers/ata.h"
#include "drivers/pic.h"
#include "drivers/gdt.h"
#include "drivers/idt.h"
#include "drivers/keyboard.h"
#include "libs/fs/fat32.h"

void _start(void) {

	text_clear();

	printf("echidnaOS\n\n");

	printf("%d bytes of memory detected.\n", mem_load_d(0x7DF9));
	printf("The kernel is %d bytes long.\n\n", mem_load_d(0x7DF5));

	printf("Initialising PIC...");

	map_PIC(0x20, 0x28);	// map the PIC0 at int 0x20-0x27 and PIC1 at 0x28-0x2F

	printf(" Done.\n");

	printf("Building descriptor tables...");

	create_GDT();		// build the GDT
	create_IDT();		// build the IDT

	load_segments();	// activate the GDT
	enable_ints();		// activate the IDT

	printf(" Done.\n");

	ata_device* devices = get_ata_devices();

        partition_table table; table = enumerate_partitions(devices[0]);
        
        fat32_filesystem fs = get_fs(table.partitions[0], devices[0]);
        
        text_putstring("OEM name: ");
        text_putstring(fs.oem_name);
        text_putstring("\n");
        
        text_putstring("Volume label: ");
        text_putstring(fs.volume_name);
        text_putstring("\n");

	asm("int 0x80");
            
        char last_c;
        
        while (1) {
            char c = get_last_char();
            
            if (c != last_c) {
                text_putchar(c);
                last_c = c;
                clear_last_char();
                
                // interactive "shell"
                if (c == '\n') {
                    if (strncmp("clear", get_keyboard_buffer(), 5) == 0) text_clear();
                    clear_keyboard_buffer();
                }
            }
        }
        
	printf("\nSoft halting system.");
	system_soft_halt();

}
