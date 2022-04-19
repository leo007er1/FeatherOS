[bits 16]

Gdt32:
    .NullDescriptor:
        dq 0

    .CodeDescriptor:
        dw 0xffff ; First 16 bits of the limit
        dw 0 ; First 16 bits of the Base
        db 0 ; Other 8 bits of the Base
        db 10011010b ; Access byte
        db 11001111b ; Flags + reserved bits
        db 0 ; And other 8 bits of the Base

    .DataDescriptor:
        dw 0xffff ; First 16 bits of the limit
        dw 0 ; First 16 bits of the Base
        db 0 ; Other 8 bits of the Base
        db 10010010b ; Access byte
        db 11001111b ; Flags + reserved bits
        db 0 ; And other 8 bits of the Base


Gdt32Descriptor:
    dw $ - Gdt32 - 1 ; Size
    dd Gdt32 ; Start


CodeSegment32: equ Gdt32.CodeDescriptor - Gdt32
DataSegment32: equ Gdt32.DataDescriptor - Gdt32



[bits 32]

; And after 20 minutes I got this to work. YAY!
Gdt64:
    .NullDescriptor:
        dq 0

    .CodeDescriptor:
        dw 0xffff ; First 16 bits of the limit
        dw 0 ; First 16 bits of the Base
        db 0 ; Other 8 bits of the Base
        db 10011010b ; Access byte
        db 10101111b ; Flags + reserved bits
        db 0 ; And other 8 bits of the Base

    .DataDescriptor:
        dw 0xffff ; First 16 bits of the limit
        dw 0 ; First 16 bits of the Base
        db 0 ; Other 8 bits of the Base
        db 10010010b ; Access byte
        db 11001111b ; Flags + reserved bits
        db 0 ; And other 8 bits of the Base


Gdt64Descriptor:
    dw $ - Gdt64 - 1 ; Size
    dq Gdt64 ; Start


CodeSegment64: equ Gdt64.CodeDescriptor - Gdt64
DataSegment64: equ Gdt64.DataDescriptor - Gdt64

[bits 16]