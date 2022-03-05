[org 0x7c00]


%include "Cagos/Print.asm"
%include "Cagos/ReadDisk.asm"


; Save the disk number we are at
mov [DiskNumber], dl

; Stack setup
mov bp, 0x7c00
mov sp, bp

call ReadDisk

jmp ProgramSpace


times 510-($-$$) db 0
dw 0xaa55