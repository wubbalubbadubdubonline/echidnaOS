

void system_halt(void) {
	asm("nop; nop; cli; hlt;");
}
