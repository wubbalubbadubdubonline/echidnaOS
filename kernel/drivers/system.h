#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "../libs/stdint.h"
#include "../libs/stddef.h"

#define system_halt() ({					\
	asm volatile ("cli; hlt");				\
})

#define disable_ints() ({					\
	asm volatile ("cli");					\
})

#define enable_ints() ({					\
	asm volatile ("sti");					\
})

#define io_wait() ({						\
	asm volatile (	"out 0x80, al"			\
					:						\
					: "a" (0)				\
					: );					\
})

#define port_out_b(port, value) ({				\
	asm volatile (	"out dx, al"				\
					:							\
					: "a" (value), "d" (port)	\
					: );						\
})

#define port_out_w(port, value) ({				\
	asm volatile (	"out dx, ax"				\
					:							\
					: "a" (value), "d" (port)	\
					: );						\
})

#define port_out_d(port, value) ({				\
	asm volatile (	"out dx, eax"				\
					:							\
					: "a" (value), "d" (port)	\
					: );						\
})

#define port_in_b(port) ({						\
	uint8_t value;								\
	asm volatile (	"in al, dx"					\
					: "=a" (value)				\
					: "d" (port)				\
					: );						\
	value;										\
})

#define port_in_w(port) ({						\
	uint16_t value;								\
	asm volatile (	"in ax, dx"					\
					: "=a" (value)				\
					: "d" (port)				\
					: );						\
	value;										\
})

#define port_in_d(port) ({						\
	uint32_t value;								\
	asm volatile (	"in eax, dx"				\
					: "=a" (value)				\
					: "d" (port)				\
					: );						\
	value;										\
})

#endif
