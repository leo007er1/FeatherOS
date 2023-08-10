[bits 64]
[extern pushaq]
[extern popaq]
[extern print]


[global fpuInit]
fpuInit:
    mov eax, 1
    cpuid
    test edx, 1 ; FPU bit
    jz .noFpu

    mov rax, cr0
    and ax, 0xff3 ; CLear cr0.EM and cr0.TS
    mov cr0, rax

    fninit
    fnstsw [.statusNumber]
    cmp word [.statusNumber], 0
    jnz .noFpu

    lea rdi, fpuMessage
    mov rsi, 0x57cc99
    call print

    ret

    .noFpu:
        lea rdi, noFpuMessage
        call print

        ret


.statusNumber: dw 0xa23a ; Random numbers
noFpuMessage: db "FPU not present!", 10, 0
fpuMessage: db "%bFPU enabled!", 10, 0