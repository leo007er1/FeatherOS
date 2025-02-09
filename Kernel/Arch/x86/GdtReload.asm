[bits 64]


[global gdtReload]
gdtReload:
    ; Reload other registers
    mov ax, 0x10 ; 0x10 is kernel data segment
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Reload cs with a far return
    lea rax, [.reloadCodeSeg]
    push 0x08 ; 0x8 is kernel code segment
    push rax
    retfq

    .reloadCodeSeg:
        ret
