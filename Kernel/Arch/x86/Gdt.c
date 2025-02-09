#include <Common.h>
#include <Arch/x86/Gdt.h>

// https://osdev.wiki/wiki/Global_Descriptor_Table

static gdtEntry_t gdt[gdtEntries];
static gdtr_t gdtr;


static void gdtSetEntry(uint16_t entryNum, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
    gdtEntry_t* entry = &gdt[entryNum];

    entry->base0 = base & 0xffff;
    entry->base1 = (base >> 16) & 0xff;
    entry->base2 = (base >> 24) & 0xff;
    entry->limit0 = limit & 0xffff;
    entry->limit1 = (limit >> 16) & 0x0f,
    entry->access = access;
    entry->flags = flags;
}


void gdtInit(void) {
    __asm__ volatile("cli");

    gdtSetEntry(0, 0, 0, 0, 0); // Null desc
    gdtSetEntry(1, 0, 0x000fffff, 0x9a, 0xa); // Kernel code segment(64 bit)
    gdtSetEntry(2, 0, 0x000fffff, 0x92, 0xc); // Kernel data segment(64 bit)
    gdtSetEntry(3, 0, 0x000fffff, 0xfa, 0xa); // User code segment(64 bit)
    gdtSetEntry(4, 0, 0x000fffff, 0xf2, 0xc); // User data segment(64 bit)

    gdtr.base = (uint64_t)&gdt;
    gdtr.limit = sizeof(gdt) - 1;

    __asm__ volatile("lgdt %0" : : "m"(gdtr) : "memory");
    gdtReload();

    __asm__ volatile("sti");
    log("[ %bOK%b ] GDT initialized succesfully!\n", 0x57cc99, 0xffffff);
}