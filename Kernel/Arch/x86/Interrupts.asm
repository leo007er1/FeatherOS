[bits 64]
[extern intHandler]


%macro pushaq 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rdi
    push rsi
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    mov rax, cr0
    push rax
    mov rax, cr2
    push rax
    mov rax, cr3
    push rax
    mov rax, cr4
    push rax
%endmacro


%macro popaq 0
    pop rax
    mov cr4, rax
    pop rax
    mov cr3, rax
    pop rax
    mov cr2, rax
    pop rax
    mov cr0, rax
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rsi
    pop rdi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
%endmacro


%macro setIsr 1
    [global intr%+%1]
    intr%+%1:
        push 0
        push %1

        jmp isrCommonEntry
%endmacro

%macro setIsrError 1
    [global intr%+%1]
    intr%+%1:
        push %1

        jmp isrCommonEntry
%endmacro


isrCommonEntry:
    pushaq
    cld

    ; mov ax, 0x10
    ; mov ds, ax
    ; mov es, ax
    ; mov fs, ax
    ; mov gs, ax

    mov rdi, rsp ; System V x86-64 uses rdi as the first argument for a function. (rsp is the stack pointer)
    call intHandler
    ; mov rsp, rax ; And the return value is in rax

    ; pop rax
    ; mov ds, ax
    ; mov es, ax
    ; mov fs, ax
    ; mov gs, ax

    popaq
    add rsp, 16
    iretq




; Sets every CPU exception handler and some IRQs
; https://osdev.wiki/wiki/Exceptions

setIsr 0 ; Division by 0
setIsr 1 ; Debug
setIsr 2 ; NMI
setIsr 3 ; Breakpoint
setIsr 4 ; Overflow
setIsr 5 ; Bound range exceeded
setIsr 6 ; Invalid opcode
setIsr 7 ; Device not avaiable
setIsrError 8 ; Double fault
setIsr 9 ; Coprocessor segment overrun
setIsrError 10 ; Invalid TSS
setIsrError 11 ; Segment not present
setIsrError 12 ; Stack-segment fault
setIsrError 13 ; General protection fault
setIsrError 14 ; Page fault
setIsr 15 ; Reserved
setIsr 16 ; x87 floating-point exception, unused
setIsrError 17 ; Alignment check
setIsr 18 ; Machine check
setIsr 19 ; SIMD floating-point exception
setIsr 20 ; Virtualization exception
setIsrError 21 ; Control protection exception
setIsr 22 ; All reserved
setIsr 23
setIsr 24
setIsr 25
setIsr 26
setIsr 27
setIsr 28 ; Hypervisor injection exception
setIsrError 29 ; VMM communication exception
setIsrError 30 ; Security exception
setIsr 31 ; Reserved

; IRQs
%assign i 32
%rep 224
    setIsr i
    %assign i i + 1
%endrep


[section .data]

[global intrList]
intrList:
    %assign i 0
    %rep 256
        dq intr%+i
        %assign i i + 1
    %endrep