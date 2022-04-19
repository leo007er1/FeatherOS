[bits 16]


; Prints a string only in Real Mode. Set bx to the pointer of the string
; Oh yeah just one thing, remember to null terminate your string :)
PrintString:
    push ax
    mov ah, 0x0e ; Teletype mode

    .Loop:
        cmp [bx], byte 0
        je .Exit

        mov al, [bx]
        int 0x10

        inc bx
        jmp .Loop

    .Exit:
        pop ax
        ret



; Prints a hexadecimal value in Real Mode. Set bx to the value you want to print
; PrintHex:
;     push cx
;     push bx
;     push ax
;     push dx

;     mov bx, .HexPrefix
;     call PrintString

;     pop bx
;     mov cx, 0x0404

;     .Loop:
;         rol bx, cl
;         mov ax, 0x0e0f
;         and al, dl

;         add al, 0x90
;         daa
;         add al, 0x40
;         daa

;         int 0x10
;         dec ch
;         jnz .Loop


;     pop cx
;     pop ax
;     pop dx

;     ret



; .HexPrefix: db "0x", 0