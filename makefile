C_FILES = $(wildcard kernel/*.c wildcard kernel/libs/*.c wildcard kernel/drivers/${ARCH}/*.c)
ASM_FILES = $(wildcard kernel/drivers/${ARCH}/*.asm)
C_OBJ = ${C_FILES:.c=.o}
ASM_OBJ = ${ASM_FILES:.asm=.o}
OBJ = ${C_OBJ} ${ASM_OBJ}

CFLAGS = -std=gnu99 -nostdlib -nostartfiles -nodefaultlibs -fno-builtin -masm=intel
LDFLAGS = -Ttext 0x100000 -Tdata 0x180000 --oformat binary

ifeq (${ARCH}, i386)
ARCHCFLAGS = -m32 -D__32BIT__
ARCHLDFLAGS = -melf_i386
ARCHNASMFLAGS = -f elf32
else ifeq (${ARCH}, x86_64)
ARCHCFLAGS = -m64 -D__64BIT__
ARCHLDFLAGS = -melf_x86_64
ARCHNASMFLAGS = -f elf64
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
	rm -rf ${OBJ} bootloader.bin kernel.sys

bootloader.bin: bootloader/bootloader_${ARCH}.asm
	nasm bootloader/bootloader_${ARCH}.asm -f bin -o bootloader.bin

kernel.sys: ${OBJ}
	ld ${LDFLAGS} ${ARCHLDFLAGS} $^ -o $@

%.o: %.c
	gcc ${CFLAGS} ${ARCHCFLAGS} -c $< -o $@

%.o: %.asm
	nasm $< ${ARCHNASMFLAGS} -o $@

clean:
	rm -rf mnt
	rm -rf ${OBJ} bootloader.bin kernel.sys
