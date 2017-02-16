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
