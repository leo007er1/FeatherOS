section .text
    [bits 64]
    [extern KernelInit]

    call KernelInit ; Starts the scary mighty kernel

    jmp $