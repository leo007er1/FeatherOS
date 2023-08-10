[bits 64]
[global interruptList]
[extern generalExceptionHandler]
[extern keyboardIrqHandler]


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
%endmacro


%macro popaq 0
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


isrCommonHandler:
    pushaq
    cld

    mov rdi, rsp ; System V x86-64 uses rdi as the first argument for a function. (rsp is the stack pointer)
    call generalExceptionHandler
    mov rsp, rax ; And the return value is in rax

    popaq
    add rsp, 16
    iretq



%macro setIsr 1
    isr%+%1:
        push 0
        push %1

        jmp isrCommonHandler
%endmacro

%macro setIsrError 1
    isr%+%1:
        push %1

        jmp isrCommonHandler
%endmacro

; Sets every CPU exception handler
; https://wiki.osdev.org/Exceptions

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
; From this point here there are unused exceptions

; IRQ 1, keyboard
[global isr33]
isr33:
    push 1
    push 33

    pushaq
    cld

    mov rdi, rsp ; System V x86-64 uses rdi as the first argument for a function. (rsp is the stack pointer)
    call keyboardIrqHandler
    mov rsp, rax ; And the return value is in rax

    popaq
    add rsp, 16
    iretq



%assign i 0
interruptList:
    %rep 19
        dq isr%+i
        %assign i i + 1
    %endrep
