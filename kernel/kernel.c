#include "libs/variables.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include "libs/partition.h"
#include "libs/memory.h"
#include <ctype.h>
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

void done_msg(void);
void kernel_shell(void);

void _start(void) {
	char buf[16];
        char buf_test[512] = {1};
        uint8_t selected_partition;
        uint32_t lba1, lba2, count = 1;
        
        
	uint32_t memory_size = mem_load_d(0x7DF9);
	uint32_t kernel_size = mem_load_d(0x7DF5);
	uint32_t available_page = (0x1000000+kernel_size)/0x400000;
	if ((0x1000000+kernel_size)%0x400000) available_page++;
        
	text_clear();

	text_putstring("echidnaOS\n\n");

	text_putstring(itoa(memory_size, buf, 10));
	text_putstring(" bytes of memory detected.\n");
	text_putstring("The kernel is ");
	text_putstring(itoa(kernel_size, buf, 10));
	text_putstring(" bytes long.\n\n");

	text_putstring("Initialising PIC...");

	map_PIC(0x20, 0x28);	// map the PIC0 at int 0x20-0x27 and PIC1 at 0x28-0x2F

        done_msg();

	text_putstring("Building descriptor tables...");

	create_GDT();		// build the GDT
	create_IDT();		// build the IDT

	load_segments();	// activate the GDT
	enable_ints();		// activate the IDT

        done_msg();

	if ((available_page*0x400000)+0x400000 >= memory_size) panic("insufficient memory to start ramdrive");
	memory_map(0, (available_page*0x400000), 0xD0000000, 0);	// allocate 4 MiB of memory for the ramdrive
	available_page++;

	kernel_shell();

// anyone working on this stuff below should implement it properly into separate functions, then add commands to the shell below

      //  devices_initalize();
        
   //     fat32_filesystem fs;
   //     partition_table table;

	/*
                    if (strncmp("read", input, 4) == 0) {
                        kbuf += 5;
                        disk_load_sector(input, lba1, count, *buf);
                    }
                    
                    if (strncmp("write", input, 5) == 0) {
                        kbuf += 6;
                        disk_write_sector(input, lba1, count, *buf);
                    }
                    
                    if (strncmp("initpart", kbuf, 8) == 0) {
                        kbuf += 9;
                        
                        table = enumerate_partitions(kbuf);      
                    }
                    
                    if (strncmp("selectpart", kbuf, 10) == 0) {
                        kbuf += 11;
                        selected_partition = atoi(kbuf);
                        
                    }
                    
                    if (strncmp("selectlba1", kbuf, 10) == 0) {
                        kbuf += 11;
                        lba1 = atoi(kbuf);
                    }
                    
                    if (strncmp("selectlba2", kbuf, 10) == 0) {
                        kbuf += 11;
                        lba2 = atoi(kbuf);
                    }
                    
                    if (strncmp("selectcount", kbuf, 11) == 0) {
                        kbuf += 12;
                        count = atoi(kbuf);
                    }
                    
                    
                    if (strncmp("sectcopy", kbuf, 8) == 0) {
                        kbuf += 9;
                        char* k = strstr(kbuf, " ");
                        kbuf[k - kbuf] = '\0';
                        disk_load_sector(kbuf, lba1, count, 0xD0000000);
                        disk_write_sector(k, lba2, count, 0xD0000000);
                    }
                    
                    if (strncmp("initfs", kbuf, 6) == 0) {
                        kbuf += 7;
                        fs = get_fs(table.partitions[selected_partition], kbuf);                         
                        printf("OEM name: %s\n", fs.oem_name);
                        printf("Volume label: %s\n", fs.volume_name);
                        printf("Serial number: %x\n", fs.serial_number);
                        printf("Exists: %s\n", fs.exists != 0 ? "true" : "false");
                        
                    }
                    clear_keyboard_buffer();
                
                    printf("> ");

		
                }
            } */

}

void done_msg(void) {
	char old_palette = text_get_text_palette();
	text_set_cursor_pos(74, text_get_cursor_pos_y());
	text_putchar('[');
	text_set_text_palette(0x02);
	text_putstring("DONE");
	text_set_text_palette(old_palette);
	text_putchar(']');
}

void kernel_shell(void) {
	char input[256]={0};

	// kernel side shell

	text_putstring("\nKernel shell: \n\n");

	while (1) {
		text_putstring("> ");

		keyboard_getstring(input, 256);

		text_putchar('\n');

		if (strcmp("clear", input) == 0) text_clear();
		else if (strcmp("panic", input) == 0) panic("manually triggered panic");
		else if (input[0]!=0) text_putstring("Invalid command.\n");
	}
}
