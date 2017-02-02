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

kernel.sys: kernel.o ${LIBS_OBJ}
	ld ${LDFLAGS} ${ARCHLDFLAGS} $^ -o $@

kernel.o: kernel/kernel.c
	gcc ${CFLAGS} ${ARCHCFLAGS} -c $< -o $@

%.o: %.c
	gcc ${CFLAGS} ${ARCHCFLAGS} -c $< -o $@

clean:
	rm kernel/libs/*.o kernel.o
