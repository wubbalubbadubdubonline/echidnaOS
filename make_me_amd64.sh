#!/bin/bash

printf "== echidnaOS autobuild tool ==\n\n"

if [[ $EUID -ne 0 ]]; then
printf "Error: This script must be run as root, because of the mounting.\n"
exit 1
fi

printf "All data previously stored in 'echidna.img' will be lost (if it exists)!\n"
printf "A 'echidna.old' backup will be made as a failsafe.\n"
rm echidna.old 2> /dev/null
mv echidna.img echidna.old 2> /dev/null

printf "Assembling bootloader...\n"
nasm bootloader/bootloader_amd64.asm -f bin -o echidna.img

printf "Expanding image...\n"
dd bs=512 count=2872 status=none if=/dev/zero >> echidna.img

printf "Creating temporary folder to store binaries...\n"
mkdir tmp

printf "Compiling kernel...\n"
gcc -c -m64 -nostdlib -nostartfiles -nodefaultlibs -fno-builtin "kernel/kernel.c" -o "tmp/kernel.o" -masm=intel
ld -o "tmp/kernel.sys" -Ttext 0x100000 "tmp/kernel.o" --oformat binary -melf_x86_64
rm "tmp/kernel.o"

printf "Compiling content of the C sources in the 'sources' directory...\n"
for c_file in sources/*.c
do
	base_name=${c_file%.c}
	base_name=${base_name:8}
	printf "Compiling '$c_file'...\n"
	gcc -c -m64 -nostdlib -nostartfiles -nodefaultlibs -fno-builtin "$c_file" -o "tmp/${base_name}.o" -masm=intel
	ld -o "tmp/${base_name}.bin" -Ttext 0x100 "tmp/${base_name}.o" --oformat binary -melf_x86_64
	rm "tmp/${base_name}.o"
done

printf "Creating mount point for image...\n"
mkdir mnt

printf "Mounting image...\n"
mount echidna.img ./mnt
sleep 3

printf "Copying files to image...\n"
cp -r extra/* mnt/ 2> /dev/null
cp tmp/* mnt/
sleep 3

printf "Unmounting image...\n"
umount ./mnt
sleep 3

printf "Cleaning up...\n"
rm -rf tmp
rm -rf mnt

printf "Done!\n"

exit 0
