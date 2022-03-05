
GDTStart:
    GDTNullDescriptor:
        dd 0x0
        dd 0x0
    GDTCodeDescriptor:
        dw 0xFFFF ; Limite (lo abbiamo messo al massimo valore di 20 bit)
        dw 0x0000 ; 16 bit +
        db 0x00 ; 8 bit = 24 bit
        db 10011010b ; Privilegi, tipo e falgs combinati
        db 11001111b ; Altri flag + limite (ultimi 4 bit)
        db 0x00 ; Ultimi 8 bit della base (24 + 8 = 32 bit)
    GDTDataDescriptor:
        dw 0xFFFF ; Limite (lo abbiamo messo al massimo valore di 20 bit)
        dw 0x0000 ; 16 bit +
        db 0x00 ; 8 bit = 24 bit
        db 10010010b ; Privilegi, tipo e falgs combinati
        db 11001111b ; Altri flag + limite (ultimi 4 bit)
        db 0x00 ; Ultimi 8 bit della base (24 + 8 = 32 bit)


GDTEnd:


GDTDescriptor:
    GDTSize:
        dw GDTEnd - GDTStart - 1 ; Grandezza
        dq GDTStart


; Costanti
CodeSegment equ GDTCodeDescriptor - GDTStart
DataSegment equ GDTDataDescriptor - GDTStart

[bits 32]

ChangeGDTto64bits:
    mov [GDTCodeDescriptor + 6], byte 10101111b
    mov [GDTDataDescriptor + 6], byte 10101111b

    ret

[bits 16]







