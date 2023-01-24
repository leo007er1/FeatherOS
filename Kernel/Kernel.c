
#include "Include/Common.h"
#include <Include/Arch/x86/CPU/IDT.h>



void __attribute__((section(".entry"))) KernelInit(void) {
    // IdtInit(); // KABUUMM

    for (;;) {
        __asm__ volatile("hlt");
    }

}