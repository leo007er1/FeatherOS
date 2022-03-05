Print:
    push ax
    push bx

    mov ah, 0x0e ; Teletype mode

    .printLoop:
        cmp [bx], byte 0 ; Siamo arrivati alla fine della stringa?
        je .exit

        mov al, [bx] ; Spostiamo il carattere
        int 0x10 ; BIOS interrupt
        inc bx

        jmp .printLoop

    .exit:
        pop ax
        pop bx

        ret
