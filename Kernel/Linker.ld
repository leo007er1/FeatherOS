
/* Basically stolen from limine barebones github repo */

/* x86_64 elf64 output file pls */
OUTPUT_FORMAT(elf64-x86-64)
OUTPUT_ARCH(i386:x86-64)

ENTRY(kernelInit)


/* Programs headers */
PHDRS {
    text    PT_LOAD    FLAGS((1 << 0) | (1 << 2)) ; /* Execute and read */
    rodata  PT_LOAD    FLAGS((1 << 2)) ;            /* Read only */
    data    PT_LOAD    FLAGS((1 << 1) | (1 << 2)) ; /* Write and read */
}


SECTIONS {
    /* We wanna be placed in the topmost 2GiB of the address space, for optimisations and because that is what the Limine spec mandates. */
    /* Any address in this region will do, but often 0xffffffff80000000 is chosen as the beginning of the region. */
    . = 0xffffffff80000000;

    .text : {
        *(.text .text.*)
    } :text

    /* Move to the next memory page for .rodata */
    . += CONSTANT(MAXPAGESIZE);

    .rodata : {
        *(.rodata .rodata.*)
    } :rodata

    /* Move to the next memory page for .data */
    . += CONSTANT(MAXPAGESIZE);

    .data : {
        *(.data .data.*)
    } :data

    .bss : {
        *(COMMON)
        *(.bss .bss.*)
    } :data

    /* Discard .note.* and .eh_frame since they may cause issues on some hosts. */
    /DISCARD/ : {
        *(.eh_frame)
        *(.note .note.*)
    }
}