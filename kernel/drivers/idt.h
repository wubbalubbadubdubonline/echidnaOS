#ifndef __IDT_H__
#define __IDT_H__

#include "../libs/stdint.h"
#include "../libs/stddef.h"

// idt building functions
void build_idt(uint32_t table_offset, uint8_t entry_count);
void build_idt_entry(uint32_t table_offset, uint8_t vector, uint16_t selector, uint32_t offset, uint8_t type);

// ISRs
void handler_simple(void);
void handler_code(void);
void handler_irq_pic0(void);
void handler_irq_pic1(void);
void keyboard_isr(void);

#endif
