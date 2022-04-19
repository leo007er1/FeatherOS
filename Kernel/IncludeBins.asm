[bits 64]


; Macro that includes a binary and sets it as global in rodata
%macro IncludeBin 2
    section .rodata
        [global %1]

    %1:
        incbin %2
        db 0

%endmacro



IncludeBin VgaOsTitle, "./Src/OsTitle.txt"