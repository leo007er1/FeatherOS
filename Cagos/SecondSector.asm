[org 0x7e00]
[bits 16]

jmp InitProtectedMode


%include "./Cagos/SecondSectorStuff/A20.asm"
%include "./Cagos/SecondSectorStuff/GDT.asm"


InitProtectedMode:
    ; Clears screen and sets text mode
    mov ah, 0
    mov al, 3
    int 0x10

    call EnableA20Line ; Would be cool to access all of our memory
    cli
    lgdt [Gdt32Descriptor]

    push eax

    ; Changes the last bit of the control register 0 to 1
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    pop eax

    jmp CodeSegment32:EnterProtectedMode



; 32 bits!
[bits 32]

%include "./Cagos/SecondSectorStuff/Print.asm"
%include "./Cagos/SecondSectorStuff/CPU.asm"
%include "./Cagos/SecondSectorStuff/Paging.asm"


EnterProtectedMode:
    ; Updates segment registers
    mov ax, 0x10 ; 0x10 is the data segment
    mov ds, ax
    mov gs, ax
    mov fs, ax
    mov es, ax
    mov ss, ax

    ; Changes stack
    mov ebp, 0x90000
    mov esp, ebp

    call DetectCpuId
    call DetectLongMode
    call SetUpPaging
    
    lgdt [Gdt64Descriptor]

    jmp CodeSegment64:EnterLongMode



; 64 BITS!!!
[bits 64]


EnterLongMode:
    mov edi, 0xB8000
    mov rax, 0x1F201F201F201F20
    mov ecx, 500
    rep stosq

    ; Jumps to KernelEntry.asm
    mov rbx, 0x1000
    jmp rbx
    


