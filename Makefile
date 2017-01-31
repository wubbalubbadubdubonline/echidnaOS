CC = i686-elf-gcc
ASSEMBLER = i686-elf-as
CFLAGS = -ffreestanding -Wall -Wextra

C_SOURCES = ${wildcard kernel/*.c}
HEADERS = ${wildcard kernel/*.h}

OBJ = ${C_SOURCES:.c=.o boot/boot.o}

run: os-image.iso
	
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@

%.o: %.s
	${ASSEMBLER} $< -o $@

os-image.bin: ${OBJ}
	${CC} -T linker.ld -o os-image.bin -ffreestanding -lgcc -nostdlib 

os-image.iso: os-image.bin
	cp os-image.bin isodir/boot/os-image.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso isodir

clean:
	rm kernel/*.o boot/*.o *.bin *.iso