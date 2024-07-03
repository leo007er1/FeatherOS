
#include <Common.h>
#include <Arch/x86/Idt.h>
#include <Screen/Terminal.h>
#include <Screen/Framebuffer.h>


/* IDT
 0 - 31 -> CPU exceptions
 then idk

*/

static idtEntry_t idt[idtEntries];
static idtr_t idtr;
extern void* interruptList[];
extern void* isr33;



void picSendEoi(uint8_t irq) {
    if (irq >= 8) {
        outPortB(picCommandSlave, 0x20);
        return;
    }

    outPortB(picCommandMaster, 0x20);
}


void picRemap(void) {
    // Send ICWs and remap IRQs
    outPortB(picCommandMaster, 0x11);
    outPortB(picCommandSlave, 0x11);
    outPortB(picDataMaster, 0x20); // IRQ 0 to 7
    outPortB(picDataSlave, 0x28); // IRQ 8 to 15
    outPortB(picDataMaster, 0x4); // Master IRQ pin 2 is connected to slave
    outPortB(picDataSlave, 0x2);
    outPortB(picDataMaster, 0x1); // 8086 mode pls, not 8080
    outPortB(picDataSlave, 0x1);

    // Mask all IRQs
    outPortB(picDataMaster, 0xff);
    outPortB(picDataSlave, 0xff);
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

    // To use the IOAPIC and local APIC, we need to disable 8259 PIC emulation
    picRemap();

    // Sets all exception handlers
    for (uint16_t i = 0; i < 19; i++) {
        idtSetEntry(i, (uint64_t)interruptList[i], 0, idtIntFlags);
    }

    idtSetEntry(33, (uint64_t)isr33, 0, idtIntFlags);

    idtr.limit = sizeof(idt) - 1;
    idtr.address = (uint64_t)&idt;
    __asm__("lidt %0" : : "m"(idtr));

    __asm__ volatile("sti");
}