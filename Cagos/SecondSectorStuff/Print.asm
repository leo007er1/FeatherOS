[bits 32]

; Don't be confused with the Print.asm file in the bootloader main directory, this is for Protected mode

VgaMemory: equ 0xb8000
Color: equ 0x0f ; Foreground and background color


; Prints a string in Protected Mode. Set ebx to the string you want to print
PrintString:
    pusha
    mov ecx, VgaMemory

    .Loop:
        cmp [ebx], byte 0
        je .Exit

        mov al, [ebx]
        mov ah, Color

        mov [ecx], ax ; Moves character to video memory

        add ecx, 2 ; 2 because a byte is the actual character, the other byte the color
        inc ebx ; Next character

        jmp .Loop


    .Exit:
        popa

        ret

