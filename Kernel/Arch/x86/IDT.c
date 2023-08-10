
#include <Common.h>
#include <Arch/x86/IDT.h>
#include <Arch/x86/ISR.h>
#include <Screen/Terminal.h>
#include <Arch/x86/PIC.h>
#include <Screen/Framebuffer.h>



/* IDT
 0 - 31 -> CPU exceptions
 then idk

*/


void generalExceptionHandler(cpuStatus_t* cpuStatus) {
    clearScreen(0x000000);

    print(R"(
                            ...
                            ;::::;
                        ;::::; :;
                        ;:::::'   :;
                        ;:::::;     ;.
                    ,:::::'       ;           OOO\
                    ::::::;       ;          OOOOO\
                    ;:::::;       ;         OOOOOOOO
                    ,;::::::;     ;'         / OOOOOOO
                    ;:::::::::`. ,,,;.        /  / DOOOOOO
                .';:::::::::::::::::;,     /  /     DOOOO
                ,::::::;::::::;;;;::::;,   /  /        DOOO
                ;`::::::`'::::::;;;::::: ,#/  /          DOOO
                :`:::::::`;::::::;;::: ;::#  /            DOOO
                ::`:::::::`;:::::::: ;::::# /              DOO
                `:`:::::::`;:::::: ;::::::#/               DOO
                :::`:::::::`;; ;:::::::::##                OO
                ::::`:::::::`;::::::::;:::#                OO
                `:::::`::::::::::::;'`:;::#                O 
                `:::::`::::::::;' /  / `:#                  
                ::::::`:::::;'  /  /   `#

                          %bOh no! An exception!%b
                
                The %bmagic reaper%b just destroyed FeatherOS!
                   %bKill him by restarting the computer!)", 0xef233c, 0xffffff, 0x8338ec, 0xffffff, 0x57cc99);


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

    idtSetEntry(33, (uint64_t)isr33, 0, idtIntFlags);

    setIdt(sizeof(idt) - 1, &idt);

    // To use the IOAPIC and local APIC, we need to disable 8259 PIC emulation
    picDisable();

    __asm__ volatile("sti");
}