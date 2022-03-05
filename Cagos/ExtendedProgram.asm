

jmp EnterProtectedMode

%include "Cagos/GDT.asm"
%include "Cagos/Print.asm"
%include "Cagos/CpuChecks.asm"
%include "Cagos/Paging.asm"



EnterProtectedMode:
    call EnableA20Line
    cli ; Disable BIOS interrupts
    lgdt [GDTDescriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp CodeSegment:StartProtectedMode


; TODO: redo this label for better compatibility and stability
EnableA20Line:
    in al, 0x92
    or al, 2
    out 0x92, al

    ret



[bits 32]

StartProtectedMode:
    mov ax, DataSegment
    mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

    mov [0xb8000], byte 'H'
	mov [0xb8002], byte 'e'
	mov [0xb8004], byte 'l'
	mov [0xb8006], byte 'l'
	mov [0xb8008], byte 'o'
	mov [0xb800a], byte ' '
	mov [0xb800c], byte 'W'
	mov [0xb800e], byte 'o'
	mov [0xb8010], byte 'r'
	mov [0xb8012], byte 'l'
	mov [0xb8014], byte 'd'

    call CheckCpuIdSupport
    call CheckSupportLongMode
    call SetUpIdentityPaging
    call ChangeGDTto64bits

    jmp CodeSegment:Start64Bit



[bits 64]
[extern kernel_start]

Start64Bit:
    mov edi, 0xb8000
    mov rax, 0x1f201f201f201f20
    mov ecx, 500
    rep stosq ; Clears the screen

    call kernel_start

    jmp $




; Fills 4 settori with 0
times 2048-($-$$) db 0