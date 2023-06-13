[bits 64]

[extern gdtr]
[extern idtr]
[global setGdt]
[global reloadGdt]
[global setIdt]


setGdt:
    mov [gdtr], si ; Set limit
    mov [gdtr + 2], rsi ; Set base
    lgdt [gdtr]

    ret

reloadGdt:
    ; Reload cs with a far return
    lea rax, [.reloadCodeSeg]
    push 0x08 ; 0x8 is kernel code segment
    push rax
    retfq

    .reloadCodeSeg:
        ; Reload other registers
        mov ax, 0x10 ; 0x10 is kernel data segment
        mov ds, ax
        mov ss, ax
        mov es, ax
        mov fs, ax
        mov gs, ax

        ret

setIdt:
    mov [idtr], si ; Set limit
    mov [idtr + 2], rsi ; Set address
    lidt [idtr]

    ret
