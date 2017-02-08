/* stub kernel */

#include "libs/stddef.h"
#include "libs/stdint.h"
#include "libs/string.h"
#include "drivers/system.h"
#include "drivers/textdrv.h"

void _start(void) {

	magic_breakpoint();

	text_clear();

	text_putchar(0x00);
	text_putstring("echidnaOS\n\nhello world\b\naaaa\b");

	system_halt();

}
