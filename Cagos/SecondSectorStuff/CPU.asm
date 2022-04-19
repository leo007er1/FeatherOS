[bits 32]


DetectCpuId:
    pushfd
    pop eax
    mov ecx, eax

    ; Inverts Id bit
    xor eax, 1 << 21

    push eax
    popfd

    pushfd
    pop eax
    push ecx
    popfd

    ; If eax and ecx aren't equal CpuId is supported
    xor eax, ecx
    jz NoLongMode

    ret



DetectLongMode:
    ; Tests if extended processor information is available
    mov eax, 0x80000000
    cpuId
    cmp eax, 0x80000001
    jb NoLongMode

    ; Tests if long mode is available
    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz NoLongMode

    ret




NoLongMode:
    cli
    hlt