
#include <Arch/x86/Idt.h>
#include <IO/Keyboard.h>


/* IDT
 0 - 31 -> CPU exceptions
 32 -> IRQ0 PIT
 33 -> IRQ1 keyboard

*/

static idtEntry_t idt[idtEntries];
static idtr_t idtr;
extern void setIdt();
extern void* interruptList[];
extern void isr33();




static void idtSetEntry(uint8_t vector, void* isr, uint8_t ist, uint8_t flags) {
    idtEntry_t* entry = &idt[vector];

    entry->address0 = (uint64_t)isr & 0xFFFF;
    entry->address1 = ((uint64_t)isr >> 16) & 0xFFFF;
    entry->address2 = (uint64_t)isr >> 32;
    entry->segSelector = kernelCs;
    entry->ist = ist;
    entry->flags = flags;
    entry->zero = 0;
}


void idtInit(void) {
    __asm__ volatile("cli");

    picRemap();

    // Sets all exception handlers
    for (uint16_t i = 0; i < 33; i++) {
        idtSetEntry(i, interruptList[i], 0, idtIntFlags);
    }

    idtr.limit = sizeof(idt) - 1;
    idtr.address = (uint64_t)&idt;
    __asm__("lidt %0" : : "m"(idtr));

    __asm__ volatile("sti");
}