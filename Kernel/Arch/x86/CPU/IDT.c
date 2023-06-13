
#include <Common.h>
#include <CPU/IDT.h>

#define idtIntFlags 0x8e
#define idtTrapFlags 0x8f


/* IDT
 0 - 31 -> CPU exceptions
 then idk

*/


static idtEntry_t idt[256];
idtr_t idtr;

extern char genericInterruptStub[];


static void idtSetEntry(uint8_t vector, uint64_t address, uint8_t ist, uint8_t flags) {
    idtEntry_t* entry = &idt[vector];

    entry->address0 = address & 0xFFFF;
    entry->segSelector = 0x08; // Kernel code segment selector
    entry->ist = ist;
    entry->flags = flags;
    entry->address1 = (address >> 16) & 0xFFFF;
    entry->address2 = address >> 32;
    entry->zero = 0;
}


void idtInit(void) {
    __asm__ volatile("cli");

    // Let's set all 256 entries
    for (uint16_t i = 0; i < 256; i++) {
        idtSetEntry(i, (uint64_t)genericInterruptStub, 0, idtIntFlags);
    }

    setIdt(sizeof(idt) - 1, &idt);

    __asm__ volatile("sti");
}