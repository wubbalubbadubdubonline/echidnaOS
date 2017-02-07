C_FILES = $(wildcard kernel/*.c wildcard kernel/libs/*.c wildcard kernel/drivers/*.c wildcard kernel/drivers/video/*.c)
C_OBJ = ${C_FILES:.c=.o}

CFLAGS = -std=gnu99 -nostdlib -nostartfiles -nodefaultlibs -fno-builtin -masm=intel
LDFLAGS = -Ttext 0x100000 -Tdata 0x180000 --oformat binary

ifeq (${ARCH}, i386)
ARCHCFLAGS = -m32 -D__32BIT__
ARCHLDFLAGS = -melf_i386
else ifeq (${ARCH}, x86_64)
ARCHCFLAGS = -m64 -D__64BIT__
ARCHLDFLAGS = -melf_x86_64
else
$(error ARCH variable invalid, available architectures: i386, x86_64)
endif

echidna.img: kernel.sys bootloader.bin
	cp bootloader.bin echidna.img
	dd bs=512 count=2872 status=none if=/dev/zero >> echidna.img
	mkdir mnt
	mount echidna.img ./mnt
	sleep 3
	cp kernel.sys mnt/
	sleep 3
	umount ./mnt
	sleep 3
	rm -rf mnt
	rm -rf ${C_OBJ} bootloader.bin kernel.sys

bootloader.bin: bootloader/bootloader_${ARCH}.asm
	nasm bootloader/bootloader_${ARCH}.asm -f bin -o bootloader.bin

kernel.sys: ${C_OBJ}
	ld ${LDFLAGS} ${ARCHLDFLAGS} $^ -o $@

%.o: %.c
	gcc ${CFLAGS} ${ARCHCFLAGS} -c $< -o $@

clean:
	rm -rf mnt
	rm -rf ${C_OBJ} bootloader.bin kernel.sys
