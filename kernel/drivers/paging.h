#ifndef __PAGING_H__
#define __PAGING_H__

#include "../libs/stdint.h"
#include "../libs/stddef.h"


#if defined(__32BIT__)
void map_page(uint32_t phys_addr, uint32_t virt_addr);
#elif defined(__64BIT__)
void map_page(uint64_t phys_addr, uint64_t virt_addr);
#endif


#endif
