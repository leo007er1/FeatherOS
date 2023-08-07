[bits 64]
[extern pushaq]
[extern popaq]
[extern kprint]

; https://wiki.osdev.org/SSE


[global sseInit]
sseInit:
    mov eax, 1
    cpuid
    test edx, 1 << 25
    jz .noSse

    push rcx

    mov rax, cr0
    and ax, 0xffb ; Clear cr0.EM, coprocessor emulation
    or ax, 2 ; Set cr0.MP, coprocessor monitoring
    mov cr0, rax
    mov rax, cr4
    or ax, 3 << 9 ; Set cr4.OSFXSR and cr4.OSXMMEXCPT
    mov cr4, rax

    lea rdi, sseEnabledMessage
    call kprint

    ; Check for SSE5 and AVX support
    pop rcx
    ; test ecx, 1 << 28 ; Bit for AVX
    ; jz .noAvx
    ; test ecx, 1 << 26 ; Bit for XSAVE(used to manage extended processor states)
    ; jz .noAvx

    ; xor rcx, rcx
    ; xgetbv ; Load XCR0 register
    ; or eax, 7 ; Set AVX, SSE, X87 bits
    ; xsetbv ; Set XCR0 register

    ret

    .noAvx:
        lea rdi, noAvxMessage
        call kprint

        ret

    .noSse:
        lea rdi, noSseMessage
        call kprint

        ret



noSseMessage: db "SSE not present on x86_64 machine!?", 10, 0
noAvxMessage: db "SSE5 and AVX not supported!", 10, 0
sseEnabledMessage: db "SSE enabled", 10, 0