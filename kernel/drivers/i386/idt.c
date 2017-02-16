#include "../idt.h"
#include "../system.h"

void build_idt(uint32_t table_offset, uint8_t entry_count) {
	mem_store_w(table_offset, (entry_count*8)-1);	// idt length
	mem_store_d(table_offset+2, table_offset+6);	// idt start

	for (table_offset=table_offset+6; entry_count; entry_count--) {
		mem_store_d(table_offset, 0x00000000);
		table_offset=table_offset+4;
		mem_store_d(table_offset, 0x00000000);
		table_offset=table_offset+4;
	}
}

void build_idt_entry(uint32_t table_offset, uint8_t vector, uint16_t selector, uint32_t offset, uint8_t type) {
	table_offset=(vector*8)+(table_offset+6);
	mem_store_w(table_offset, (offset%0x10000));
	mem_store_w(table_offset+2, selector);
	mem_store_b(table_offset+4, 0x00);			// unused
	mem_store_b(table_offset+5, type);
	mem_store_w(table_offset+6, (offset/0x10000));
}
