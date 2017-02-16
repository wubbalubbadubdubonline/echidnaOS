#ifndef __IDT_H__
#define __IDT_H__

#include "../libs/stdint.h"
#include "../libs/stddef.h"


void build_idt(uint32_t table_offset, uint8_t entry_count);
void handler_simple(void);


#endif
