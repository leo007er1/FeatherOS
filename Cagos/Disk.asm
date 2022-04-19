[bits 16]

; TODO: Replace int 0x13 with ah = 0x02 to ah = 0x42
; TODO: Also need to understand what the transfer buffer is in the disk address packet for int 0x13 with ah = 0x42

ReadDisk:
    ; For now we check anyway if int 0x13 extensions are avaiable
    call CheckExtension

    clc ; Clears carry flag
    pusha ; Pushes all registers

    call ResetDisk

    clc

    ; CHS addressing
    ; We read from the 2nd sector because the first one is the boot sector
    mov ch, 0x00 ; C (cylinder)
    mov dh, 0x00 ; H (head)
    mov cl, 0x02 ; S (sector). Starts from 1, not 0. Why?

    mov al, 51 ; *NOTE: this number may be the problem to why the os doesn't work
    mov bx, 0x7e00 ; From second sector
    mov ah, 0x02
    int 0x13
    jc ReadDiskFailed

    ; Checks status. If 0 we can continue
    cmp ah, 0
    jne ReadDiskFailed

    popa ; Pops all registers

    ret



; Checks if we can use int 0x13 with ah set to 0x42
CheckExtension:
    mov ah, 0x41
    mov bx, 0x55aa

    int 0x13
    jc NoDriveExtensions ; Drive doesn't have extensions :/

    cmp bx, 0xaa55
    jnz NoBiosExtensions ; BIOS doesn't support extensions :/

    ret


; Resets the disk
ResetDisk:
    mov dl, [BootDisk]
    mov ah, 0 ; Reset, not write please
    int 0x13

    ret


; DiskAddrPacket:
;     db 0x10, 0 ; Packet size and reserved byte
;     dw 50 ; Numer of sectors to read
;     dd 
;     dq 1 ; Starting absolute block number


; Errors


NoDriveExtensions:
    mov bx, NoDriveExtensionsMessage
    call PrintString

    cli
    hlt


NoBiosExtensions:
    mov bx, NoBiosExtensionsMessage
    call PrintString

    cli
    hlt


ReadDiskFailed:
    mov bx, ReadDiskFailedMessage
    call PrintString
    ; mov bx, ah ; ah contains error code
    ; call PrintHex

    ; Permanently go to sleep, mighty cpu
    cli
    hlt


ReadDiskFailedMessage:
    db "Failed to read disk", 0


NoDriveExtensionsMessage:
    db "Drive doesn't support int 0x13 extensions", 0


NoBiosExtensionsMessage:
    db "BIOS doesn't support int 0x13 extensions", 0