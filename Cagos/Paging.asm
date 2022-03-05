
SetUpIdentityPaging:
    mov edi, 0x1000 ; Destination index
    mov cr3, edi
    xor eax, eax ; Clear eax register
    mov ecx, 4096
    rep stosd ; Clears memory
    mov edi, cr3

    ; Sets l'uint32_t to destination index = 0x2003
    mov dword [edi], 0x2003
    add edi, 0x1000
    mov dword [edi], 0x3003
    add edi, 0x1000
    mov dword [edi], 0x4003
    add edi, 0x1000

    mov ebx, 0x00000003
    mov ecx, 512

    .SetEntry:
        mov dword [edi], ebx
        add ebx, 0x1000
        add edi, 8
        loop .SetEntry
    
    mov eax, cr4
    or eax, 1 << 5 ; Sets PAE-bit, 6 bit (bit 5)
    mov cr4, eax

    ; Sets LM-bit
    mov ecx, 0xC0000080
    rdmsr ; Read from register specific model
    or eax, 1 << 8
    wrmsr ; Write from register specific model

    ; Enable paging
    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    ret