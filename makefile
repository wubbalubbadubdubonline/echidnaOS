LIBS = $(wildcard kernel/libs/*.c)
LIBS_OBJ = ${LIBS:.c=.o} 

CC = gcc

CFLAGS = -std=gnu99 -m32 -nostdlib -nostartfiles -nodefaultlibs -fno-builtin -masm=intel -D__32BIT__

kernel.sys: kernel.o ${LIBS_OBJ}
	ld -o $@ -Ttext 0x100000 $^ --oformat binary -melf_i386

kernel.o: kernel/kernel.c
	${CC} ${CFLAGS} -c $< -o $@

${LIBS_OBJ}: ${LIBS}
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm kernel/libs/*.o kernel.o
