#!/bin/bash

printf "== echidnaOS autobuild tool ==\n\n"

arch=$1

if [[ $EUID -ne 0 ]]; then
	printf "Error: This script must be run as root, because of the mounting.\n"
	exit 1
fi

if [ "$arch" == "" ]; then
	printf "Error: Architecture not specified.\n"
	printf "Available architectures: i386, x86_64.\n"
	exit 1
elif [ "$arch" == "i386" ]; then
	printf "Using the i386 architecture.\n"
elif [ "$arch" == "x86_64" ]; then
	printf "Using the x86_64 architecture.\n"
else
	printf "Error: $arch is not a valid architecture.\n"
	printf "Available architectures: i386, x86_64.\n"
	exit 1
fi

printf "All data previously stored in 'echidna.img' will be lost (if it exists)!\n"
printf "A 'echidna.old' backup will be made as a failsafe.\n"
rm echidna.old 2> /dev/null
mv echidna.img echidna.old 2> /dev/null

printf "Assembling bootloader...\n"
nasm bootloader/bootloader_$arch.asm -f bin -o echidna.img

printf "Expanding image...\n"
dd bs=512 count=2872 status=none if=/dev/zero >> echidna.img

printf "Creating temporary folder to store binaries...\n"
mkdir tmp

printf "Compiling...\n"

make ARCH=$arch

printf "Creating mount point for image...\n"
mkdir mnt

printf "Mounting image...\n"
mount echidna.img ./mnt
sleep 3

printf "Copying files to image...\n"
cp -r extra/* mnt/ 2> /dev/null
cp tmp/* mnt/
cp kernel.sys mnt/
sleep 3

printf "Unmounting image...\n"
umount ./mnt
sleep 3

printf "Cleaning up...\n"
rm -rf tmp
rm -rf mnt
rm kernel.sys

make clean

printf "Done!\n"

exit 0
