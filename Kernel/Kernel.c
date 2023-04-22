
#include "Include/Common.h"
#include "Include/Arch/x86/CPU/IDT.h"



void __attribute__((section(".entry"))) KernelInit(void) {
    // IdtInit(); // KABUUMM

    __asm__("cli");
    for (;;) {
        __asm__ volatile("hlt");
    }

}