
#include "../../../Include/Common.h"
#include "../../../Include/Arch/x86/CPU/IDT.h"


/* IDT
 0 - 31 -> CPU exceptions
 then idk

*/

// Our little bitty IDT
static IdtEntry_t idt[256];

static Idtr_t idtPtr;




void IdtSetEntry(uint8_t entryNumber, void* handler, uint16_t segmentSelector, uint8_t flags) {
    // Should be fairly easy
    IdtEntry_t* entry = &idt[entryNumber];

    entry->offset0 = (uint64_t)handler & 0xFFFF; // First 2 bytes
    entry->offset1 = ((uint64_t)handler >> 16) & 0xFFFF; // Other 2 bytes
    entry->offset2 = ((uint64_t)handler >> 32) & 0xFFFFFFFF; // Other 4 bytes
    entry->segSelector = segmentSelector;
    entry->flags = flags;

    entry->reserved = 0;
    entry->ist = 0;  // No interrupt stack table
}




void IdtInit(void) {
    __asm__ volatile("cli");

    // We set the first 32 entries because those are reserved to the cpu

    // IdtSetEntry(0, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(1, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(2, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(3, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(4, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(5, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(6, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(7, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(8, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(9, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(10, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(11, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(12, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(13, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(14, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(15, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(16, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(17, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(18, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(19, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(20, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(21, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(22, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(23, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(24, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(25, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(26, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(27, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(28, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(29, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(30, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);
    // IdtSetEntry(31, (uint64_t*)isrCommonHandler, (uint16_t)0x8, 0x8e);

    // Now let's set IDTR register to load our IDT
    idtPtr.limit = sizeof(idt) - 1;
    idtPtr.base = (uint64_t)&idt;
    // __asm__ volatile("lidt (%%rax": : "a"(&idtPtr) : "memory");

    __asm__ volatile("sti");
}