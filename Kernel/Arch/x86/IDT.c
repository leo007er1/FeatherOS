
#include <Common.h>
#include <Arch/x86/IDT.h>
#include <Arch/x86/ISR.h>



/* IDT
 0 - 31 -> CPU exceptions
 then idk

*/


void generalExceptionHandler(cpuStatus_t* cpuStatus) {
    if (cpuStatus->isrNumber == 0) {
        kprint("\nDivision by 0!\n", 0xff0000);
    } else {
        kprint("\nException!\n", 0xff0000);
    }

    __asm__ volatile("cli");
    for (;;) {
        __asm__ volatile("hlt");
    }
}


static void idtSetEntry(uint8_t vector, uint64_t address, uint8_t ist, uint8_t flags) {
    idtEntry_t* entry = &idt[vector];

    entry->address0 = address & 0xFFFF;
    entry->segSelector = kernelCs;
    entry->ist = ist;
    entry->flags = flags;
    entry->address1 = (address >> 16) & 0xFFFF;
    entry->address2 = address >> 32;
    entry->zero = 0;
}


void idtInit(void) {
    __asm__ volatile("cli");

    // Sets all exception handlers
    for (uint16_t i = 0; i < 19; i++) {
        idtSetEntry(i, (uint64_t)interruptList[i], 0, idtIntFlags);
    }

    setIdt(sizeof(idt) - 1, &idt);

    __asm__ volatile("sti");
}