/* stub kernel */

#include "libs/stddef.h"
#include "libs/stdint.h"
#include "libs/string.h"
#include "libs/system.h"
#include "drivers/textmode.h"

void _start(void) {
	int x;
	magic_breakpoint();

	port_out_b(0x10, 0x20);
	x = port_in_w(0x40);

	clear_screen();
	print("Echidna OS 0.0.0.0");

	system_halt();

}
