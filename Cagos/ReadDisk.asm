
ProgramSpace equ 0x8000


DiskNumber:
    db 0

DiskErrorMessage:
    db "Lettura del disco fallita", 0


    
ReadDisk:
    mov ah, 0x02
    mov bx, ProgramSpace
    mov al, 32 ; Number of sectors we want to read
    mov dl, [DiskNumber]

    mov ch, 0x00 ; C (cylinder)
    mov dh, 0x00 ; H (head)
    mov cl, 0x02 ; S (sector)

    int 0x13 ; BIOS interrupt
    jc ReadDiskError ; If disk reading fails

    ret


ReadDiskError:
    mov bx, DiskErrorMessage
    call Print
    
    jmp $