[bits 16]


; Shamelessly stolen from Nanobytes youtube video, thanks


KbdControllerDataPort equ 0x60
KbdControllerCommandPort equ 0x64
KbdControllerDisableKeyboard equ 0xAD
KbdControllerEnableKeyboard equ 0xAE
KbdControllerReadControlOutputPort equ 0xD0
KbdControllerWriteControlOutputPort equ 0xD1



; Enables A20 line, so we can access all the memory
EnableA20Line:
    ; Disables keyboard
    call A20WaitInput
    mov al, KbdControllerDisableKeyboard
    out KbdControllerCommandPort, al

    ; Read control output port
    call A20WaitInput
    mov al, KbdControllerReadControlOutputPort
    out KbdControllerCommandPort, al

    call A20WaitOutput
    in al, KbdControllerDataPort

    push eax

    ; Write control output port
    call A20WaitInput
    mov al, KbdControllerWriteControlOutputPort
    out KbdControllerCommandPort, al

    call A20WaitInput
    pop eax

    ; Sets A20 bit
    or al, 2
    out KbdControllerDataPort, al

    ; Enables keyboard
    call A20WaitInput
    mov al, KbdControllerEnableKeyboard
    out KbdControllerCommandPort, al

    call A20WaitInput

    ret


; Waits until stutus bit(input buffer) 2 is 0
A20WaitInput:
    in al, KbdControllerCommandPort
    test al, 2
    jnz A20WaitInput

    ret


; Waits until status bit 1(output buffer) is 1
A20WaitOutput:
    in al, KbdControllerCommandPort
    test al, 1
    jz A20WaitOutput

    ret
