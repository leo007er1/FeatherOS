; We verify that CPUID is supported by chaging the ID bit, (bit 21)
; in FLAGS register. If we can change it means CPUID is supported
CheckCpuIdSupport:
    pushfd
    pop eax
    mov ecx, eax
    xor eax, 1 << 21

    push eax
    popfd

    ; Controls if the bit changed
    pushfd
    pop eax
    
    push ecx
    popfd

    xor eax, ecx
    jz NoCpuId ; If it's equal to 0

    ret


CheckSupportLongMode:
    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz NoLongMode ; If it's equal to 0

    ret


NoCpuId:
    hlt

NoLongMode:
    hlt