; The BPB starts here

bpbOEM						db 'ECHIDNA '
bpbBytesPerSector			dw 512
bpbSectorsPerCluster		db 1
bpbReservedSectors			dw 8
bpbNumberOfFATs				db 2
bpbRootEntries				dw 224
bpbTotalSectors				dw 2880
bpbMedia					db 0xF8
bpbSectorsPerFAT			dw 9
bpbSectorsPerTrack			dw 18
bpbHeadsPerCylinder			dw 2
bpbHiddenSectors			dd 0
bpbTotalSectorsBig			dd 0
bsDriveNumber				db 0x00
bsUnused					db 0x00
bsExtBootSignature			db 0x29
bsSerialNumber				dd 0x12345678
bsVolumeLabel				db 'ECHIDNA OS '
bsFileSystem				db 'FAT12   '
