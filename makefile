LIBS = $(wildcard kernel/libs/*.c)
LIBS_OBJ = ${LIBS:.c=.o}

ifeq (${ARCH}, i386)
	CFLAGS = -std=gnu99 -m32 -nostdlib -nostartfiles -nodefaultlibs -fno-builtin -masm=intel -D__32BIT__
	LDFLAGS = -Ttext 0x100000 --oformat binary -melf_i386
else ifeq (${ARCH}, x86_64)
	CFLAGS = -std=gnu99 -m64 -nostdlib -nostartfiles -nodefaultlibs -fno-builtin -masm=intel -D__64BIT__
	LDFLAGS = -Ttext 0x100000 --oformat binary -melf_x86_64
endif

kernel.sys: kernel.o ${LIBS_OBJ}
	ld ${LDFLAGS} $^ -o $@

kernel.o: kernel/kernel.c
	gcc ${CFLAGS} -c $< -o $@

%.o: %.c
	gcc ${CFLAGS} -c $< -o $@

clean:
	rm kernel/libs/*.o kernel.o
