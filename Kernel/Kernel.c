
#include <Common.h>
#include <Screen/Framebuffer.h>
#include <Screen/Output.h>
#include <ACPI.h>



void __attribute__((section(".entry"))) kernelInit(void) {
    screenInit();
    gdtInit();
    kprint("GDT initialized succesfully!\n");
    idtInit(); // KABUUMM
    kprint("IDT initialized succesfully!\n");
    acpiInit();
    kprint("Parsed ACPI tables\n");


    __asm__ volatile("cli");
    for (;;) {
        __asm__ volatile("hlt");
    }

}