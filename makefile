LIBS = $(wildcard kernel/libs/*.c)
LIBS_OBJ = ${LIBS:.c=.o}

CFLAGS = -std=gnu99 -nostdlib -nostartfiles -nodefaultlibs -fno-builtin -masm=intel
LDFLAGS = -Ttext 0x100000 --oformat binary

ifeq (${ARCH}, i386)
	ARCHCFLAGS = -m32 -D__32BIT__
	ARCHLDFLAGS = -melf_i386
else ifeq (${ARCH}, x86_64)
	ARCHCFLAGS = -m64 -D__64BIT__
	ARCHLDFLAGS = -melf_x86_64
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

bootloader.bin: bootloader/bootloader_${ARCH}.asm
	nasm bootloader/bootloader_${ARCH}.asm -f bin -o bootloader.bin

kernel.sys: kernel.o ${LIBS_OBJ}
	ld ${LDFLAGS} ${ARCHLDFLAGS} $^ -o $@

kernel.o: kernel/kernel.c
	gcc ${CFLAGS} ${ARCHCFLAGS} -c $< -o $@

%.o: %.c
	gcc ${CFLAGS} ${ARCHCFLAGS} -c $< -o $@

clean:
	rm kernel/libs/*.o kernel.o bootloader.bin kernel.sys
