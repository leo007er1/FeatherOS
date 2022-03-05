OUTPUT_FORMAT(binary)

ENTRY(kernel_start)

INPUT(
    FileCompilati/ExtendedProgram.o
    FileCompilati/KernelMain.o
)

OUTPUT(
    FileCompilati/Kernel.bin
)

SECTIONS{
    . = 0x8000;

    .text : ALIGN(0x1000){
        *(.text)
    }

    .data : ALIGN(0x1000){
        *(.data)
    }

    .rodata : ALIGN(0x1000){
        *(.rodata)
    }

    .bss : ALIGN(0x1000){
        *(COMMON)
        *(.bss)
    }
}