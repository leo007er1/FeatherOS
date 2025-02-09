
#include <Arch/x86/Idt.h>


/* IDT
 0 - 31 -> CPU exceptions
 32 -> IRQ0 PIT
 33 -> IRQ1 keyboard

*/

static __attribute__((aligned(0x10))) idtGate_t idt[idtMaxGates];
static idtr_t idtr;



void idtSetGate(void (*handler)(), uint16_t vector, uint8_t gateType, uint8_t gateDpl) {
    if (vector > idtMaxGates) return;
    idtGate_t* gate = &idt[vector];

    gate->offset0 = (uint64_t)handler & 0xffff;
    gate->offset1 = ((uint64_t)handler >> 16) & 0xffff;
    gate->offset2 = ((uint64_t)handler >> 32) & 0xffffffff;
    gate->segSelector = 0x08;
    gate->type = gateType;
    gate->dpl = gateDpl;
    gate->present = 1;
    gate->ist = 0; // TSS not used
    gate->zero = 0;
}


void idtInit(void) {
    __asm__ volatile("cli");

    idtr.address = (uint64_t)&idt;
    idtr.limit = sizeof(idt) - 1;

    picRemap();

    // Sets all handlers
    for (uint16_t i = 0; i < idtMaxGates; i++) {
        idtSetGate(intrList[i], i, idtIntGate, 0);
    }

    __asm__("lidt %0" : : "m"(idtr) : "memory");
    __asm__ volatile("sti");

    log("[ %bOK%b ] IDT initialized succesfully!\n", 0x57cc99, 0xffffff);
}