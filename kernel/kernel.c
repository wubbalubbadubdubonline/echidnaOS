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

#define KERNEL_SELECTOR 0x18

void _start(void) {

	text_clear();

	text_putstring("echidnaOS\n\n");

	text_putstring("Initialising PIC...");
	map_PIC(0x20, 0x28);
	text_putstring(" Done.\n");

	text_putstring("Building IDT...");

	build_idt(0x80000, 0x81);		// build an 81-entry long IDT at 0x80000

			// define interrupt handlers

	build_idt_entry(0x80000, 0x00, KERNEL_SELECTOR, handler_simple, 0xee);		// int 0x00, divide by 0
	build_idt_entry(0x80000, 0x01, KERNEL_SELECTOR, handler_simple, 0xee);		// int 0x01, debug
	build_idt_entry(0x80000, 0x02, KERNEL_SELECTOR, handler_simple, 0xee);		// int 0x02, NMI
	build_idt_entry(0x80000, 0x03, KERNEL_SELECTOR, handler_simple, 0xee);		// int 0x03, breakpoint
	build_idt_entry(0x80000, 0x04, KERNEL_SELECTOR, handler_simple, 0xee);		// int 0x04, overflow
	build_idt_entry(0x80000, 0x05, KERNEL_SELECTOR, handler_simple, 0xee);		// int 0x05, bound range exceeded
	build_idt_entry(0x80000, 0x06, KERNEL_SELECTOR, handler_simple, 0xee);		// int 0x06, invalid opcode
	build_idt_entry(0x80000, 0x07, KERNEL_SELECTOR, handler_simple, 0xee);		// int 0x07, device not available
	build_idt_entry(0x80000, 0x08, KERNEL_SELECTOR, handler_code, 0xee);		// int 0x08, double fault
	build_idt_entry(0x80000, 0x09, KERNEL_SELECTOR, handler_simple, 0xee);		// int 0x09, coprocessor segment overrun
	build_idt_entry(0x80000, 0x0A, KERNEL_SELECTOR, handler_code, 0xee);		// int 0x0A, invalid TSS
	build_idt_entry(0x80000, 0x0B, KERNEL_SELECTOR, handler_code, 0xee);		// int 0x0B, segment not present
	build_idt_entry(0x80000, 0x0C, KERNEL_SELECTOR, handler_code, 0xee);		// int 0x0C, stack-segment fault
	build_idt_entry(0x80000, 0x0D, KERNEL_SELECTOR, handler_code, 0xee);		// int 0x0D, general protection fault
	build_idt_entry(0x80000, 0x0E, KERNEL_SELECTOR, handler_code, 0xee);		// int 0x0E, page fault
	build_idt_entry(0x80000, 0x0F, KERNEL_SELECTOR, handler_simple, 0xee);		// int 0x0F
	build_idt_entry(0x80000, 0x10, KERNEL_SELECTOR, handler_simple, 0xee);		// int 0x10, x87 floating point exception
	build_idt_entry(0x80000, 0x11, KERNEL_SELECTOR, handler_code, 0xee);		// int 0x11, alignement check
	build_idt_entry(0x80000, 0x12, KERNEL_SELECTOR, handler_simple, 0xee);		// int 0x12, machine check
	build_idt_entry(0x80000, 0x13, KERNEL_SELECTOR, handler_simple, 0xee);		// int 0x13, SIMD floating point exception
	build_idt_entry(0x80000, 0x14, KERNEL_SELECTOR, handler_simple, 0xee);		// int 0x14, virtualisation exception
	build_idt_entry(0x80000, 0x15, KERNEL_SELECTOR, handler_simple, 0xee);		// int 0x15
	build_idt_entry(0x80000, 0x16, KERNEL_SELECTOR, handler_simple, 0xee);		// int 0x16
	build_idt_entry(0x80000, 0x17, KERNEL_SELECTOR, handler_simple, 0xee);		// int 0x17
	build_idt_entry(0x80000, 0x18, KERNEL_SELECTOR, handler_simple, 0xee);		// int 0x18
	build_idt_entry(0x80000, 0x19, KERNEL_SELECTOR, handler_simple, 0xee);		// int 0x19
	build_idt_entry(0x80000, 0x1A, KERNEL_SELECTOR, handler_simple, 0xee);		// int 0x1A
	build_idt_entry(0x80000, 0x1B, KERNEL_SELECTOR, handler_simple, 0xee);		// int 0x1B
	build_idt_entry(0x80000, 0x1C, KERNEL_SELECTOR, handler_simple, 0xee);		// int 0x1C
	build_idt_entry(0x80000, 0x1D, KERNEL_SELECTOR, handler_simple, 0xee);		// int 0x1D
	build_idt_entry(0x80000, 0x1E, KERNEL_SELECTOR, handler_code, 0xee);		// int 0x1E, security exception
	build_idt_entry(0x80000, 0x1F, KERNEL_SELECTOR, handler_simple, 0xee);		// int 0x1F

			// define IRQ's ISRs

	build_idt_entry(0x80000, 0x20, KERNEL_SELECTOR, handler_irq_pic0, 0xee);	// IRQ 0, PIT
	build_idt_entry(0x80000, 0x21, KERNEL_SELECTOR, keyboard_isr, 0xee);		// IRQ 1, keyboard
	build_idt_entry(0x80000, 0x22, KERNEL_SELECTOR, handler_irq_pic0, 0xee);	// IRQ 2
	build_idt_entry(0x80000, 0x23, KERNEL_SELECTOR, handler_irq_pic0, 0xee);	// IRQ 3, COM2
	build_idt_entry(0x80000, 0x24, KERNEL_SELECTOR, handler_irq_pic0, 0xee);	// IRQ 4, COM1
	build_idt_entry(0x80000, 0x25, KERNEL_SELECTOR, handler_irq_pic0, 0xee);	// IRQ 5, LPT2
	build_idt_entry(0x80000, 0x26, KERNEL_SELECTOR, handler_irq_pic0, 0xee);	// IRQ 6, floppy
	build_idt_entry(0x80000, 0x27, KERNEL_SELECTOR, handler_irq_pic0, 0xee);	// IRQ 7, LPT1/spurious
	build_idt_entry(0x80000, 0x28, KERNEL_SELECTOR, handler_irq_pic1, 0xee);	// IRQ 8, CMOS RTC
	build_idt_entry(0x80000, 0x29, KERNEL_SELECTOR, handler_irq_pic1, 0xee);	// IRQ 9
	build_idt_entry(0x80000, 0x2A, KERNEL_SELECTOR, handler_irq_pic1, 0xee);	// IRQ 10
	build_idt_entry(0x80000, 0x2B, KERNEL_SELECTOR, handler_irq_pic1, 0xee);	// IRQ 11
	build_idt_entry(0x80000, 0x2C, KERNEL_SELECTOR, handler_irq_pic1, 0xee);	// IRQ 12, ps/2 mouse
	build_idt_entry(0x80000, 0x2D, KERNEL_SELECTOR, handler_irq_pic1, 0xee);	// IRQ 13, FPU
	build_idt_entry(0x80000, 0x2E, KERNEL_SELECTOR, handler_irq_pic1, 0xee);	// IRQ 14, primary ATA
	build_idt_entry(0x80000, 0x2F, KERNEL_SELECTOR, handler_irq_pic1, 0xee);	// IRQ 15, secondary ATA

	load_idt(0x80000);				// load the IDT register

	enable_ints();
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
        
	text_putstring("\nSoft halting system.");
	system_soft_halt();

}
