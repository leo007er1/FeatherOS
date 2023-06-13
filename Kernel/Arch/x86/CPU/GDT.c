#include <Common.h>
#include <CPU/GDT.h>


static gdtSeg_t gdt[5];
gdtr_t gdtr;


static void gdtEncodeEntry(uint8_t entryNumber, uint32_t limit, uint32_t base, uint8_t access, uint8_t flags) {
    gdtSeg_t* entry = &gdt[entryNumber];

    entry->limit0 = limit & 0xFFFF;
    entry->base0 = base & 0xFFFF;
    entry->base1 = (base >> 16) & 0xFF;
    entry->access = access;
    entry->limit1 = (limit >> 16) & 0xFF,
    entry->flags = flags;
    entry->base2 = (base >> 24) & 0xFF;
}


void gdtInit(void) {
    gdtEncodeEntry(0, 0, 0, 0, 0); // Null desc
    gdtEncodeEntry(1, 0x000FFFFF, 0, 0x9A, 0xA); // Kernel code desc
    gdtEncodeEntry(2, 0x000FFFFF, 0, 0x92, 0xC); // Kernel data desc
    gdtEncodeEntry(3, 0x000FFFFF, 0, 0xFA, 0xA); // User code desc
    gdtEncodeEntry(4, 0x000FFFFF, 0, 0xF2, 0xC); // User data desc

    setGdt(sizeof(gdt) - 1, &gdt);
    reloadGdt();
}