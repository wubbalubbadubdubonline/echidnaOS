#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "../libs/stdint.h"
#include "../libs/stddef.h"


#if defined(__32BIT__)
uint32_t mem_get_block_base(uint32_t block);
uint32_t mem_get_block_size(uint32_t block);
#elif defined(__64BIT__)
uint64_t mem_get_block_base(uint32_t block);
uint64_t mem_get_block_size(uint32_t block);
#endif

uint32_t mem_get_block_type(uint32_t block);
uint32_t mem_get_block_ext(uint32_t block);


#endif
