[org 0x7c00]
[bits 16]


; Since some BIOSes load at 0x00000:0x7c00 and others at 0x07c0:0x0000 we "reset" CS to 0
Start:
    jmp 0x0000:Main
    nop

    ; Avoids the overwrite of bootloader code, since some BIOSes will overwrite them for no apparent reason
    times 87 db 0


Main:
    cld

    ; Saves boot disk number, pretty useful
    mov [BootDisk], dl

    xor ax, ax ; Clears ax
    mov ds, ax
    mov es, ax

    ; Stack setup
    mov bp, 0x7c00
    mov sp, bp

    ; Boot message
    mov bh, 0 ; Page
    mov bx, BootMessage
    call PrintString

    call ReadDisk

    ; Jumps to SecondSector.asm
    jmp 0x7e0:0x0 ; 0x7e0 * 16 + 0x0 = 0x7e00



; Tells the bios in what environment we are going to be in
NotifyTargetEnvironment:
    mov ax, 0xEC00
    mov bl, 2 ; 1 = 32 bit protected mode, 2 = 64 bit long mode, 3 both
    int 0x15

    ret



BootDisk: db 0
BootMessage: db "Welcome to FeatherOS!", 10, 13, 0


%include "./Cagos/Print.asm"
%include "./Cagos/Disk.asm"



; Sets up boot sector
times 510-($-$$) db 0
dw 0xaa55