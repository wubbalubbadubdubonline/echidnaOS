#include "libs/stddef.h"
#include "libs/stdint.h"
#include "libs/string.h"
#include "libs/stdlib.h"
#include "libs/stdarg.h"
#include "libs/stdio.h"
#include "libs/math.h"
#include "libs/partition.h"
#include "libs/ctype.h"
#include "libs/panic.h"
#include "drivers/system.h"
#include "drivers/textdrv.h"
#include "drivers/ata.h"
#include "drivers/pic.h"
#include "drivers/gdt.h"
#include "drivers/idt.h"
#include "drivers/keyboard.h"
#include "libs/fs/fat32.h"
#include "drivers/device_abstraction.h"

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

        set_ata_devices(get_ata_devices());
        
        partition_table table; table = enumerate_partitions(0b00000000);        // 0b00000000 is ATA Primary Master
        
        fat32_filesystem fs = get_fs(table.partitions[0], 0b00000000);          // 0b00000000 is ATA Primary Master
        
        printf("OEM name: %s\n", fs.oem_name);
        printf("Volume label: %s\n", fs.volume_name);
        printf("Serial number: %x\n", fs.serial_number);
        printf("Exists: %s\n", fs.exists != 0 ? "true" : "false");
            
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
                    if (strncmp("panic", get_keyboard_buffer(), 5) == 0) panic("manually triggered panic");
                    clear_keyboard_buffer();
                }
            }
        }
        
	printf("\nSoft halting system.");
	system_soft_halt();

}
