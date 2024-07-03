[bits 64]
[extern pushaq]
[extern popaq]
[extern log]

; https://wiki.osdev.org/SSE


[global sseInit]
sseInit:
    mov eax, 1
    cpuid
    test edx, 1 << 25 ; SSE bit
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
    mov rsi, 0x57cc99
    call log

    pop rcx

    ; Check for SSE5 and AVX support(code from Intel sdm vol. 1 14.3)
    test ecx, 1 << 28 ; Bit for AVX
    jz .noAvx
    test ecx, 1 << 26 ; Bit for XSAVE(used to manage extended processor states)
    jz .noAvx

    and ecx, 018000000h
    cmp ecx, 018000000h ; Check for OSXSAVE and AVX
    jne .noAvx

    xor rcx, rcx
    xgetbv
    and eax, 06h
    cmp eax, 06h ; Check for XMM and YMM support
    jne .noAvx

    mov rax, cr4
    or rax, 1 << 18 ; Set cr4.OSXSAVE bit
    mov cr4, rax

    xor rcx, rcx
    xgetbv ; Load XCR0 register
    or eax, 7 ; Set AVX, SSE, X87 bits
    xsetbv ; Set XCR0 register

    lea rdi, avxEnabledMessage
    mov rsi, 0x57cc99
    call log

    ret

    .noAvx:
        lea rdi, noAvxMessage
        lea rsi, 0xef233c
        call log

        ret

    .noSse:
        lea rdi, noSseMessage
        mov rsi, 0xef233c
        call log

        ret



noSseMessage: db "%bSSE not present on x86_64 machine!?", 10, 0
noAvxMessage: db "%bSSE5 and AVX not supported!", 10, 0
sseEnabledMessage: db "%bSSE enabled", 10, 0
avxEnabledMessage: db "%bAVX enabled", 10, 0