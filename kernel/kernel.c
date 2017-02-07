/* stub kernel */

#include "libs/stddef.h"
#include "libs/stdint.h"
#include "libs/string.h"
#include "libs/system.h"
#include "drivers/textmode.h"

void _start(void) {

	magic_breakpoint();

	clear_screen();
	print("Echidna OS 0.0.0.0");

	system_halt();

}
