[bits 32]


; Sets up identity paging, where physical memory is mapped as virtual memory
SetUpPaging:
    ; Clears PML4T, PDPT, PDT and PT
    mov edi, 0x1000
    mov cr3, edi
    xor eax, eax
    mov ecx, 4096
    rep stosd
    mov edi, cr3

    ; Sets up PML4T, PDPT, PDT and PT
    ; 2003 and not 2000 because the first 2 bits says if the page is present, readable and writable
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

    ; Sets PAE bit
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    ; Sets LM bit
    mov ecx, 0xC0000080 ; 0xC0000080 is the EFER MSR
    rdmsr
    or eax, 1 << 8
    wrmsr

    ; Enables paging
    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    ret