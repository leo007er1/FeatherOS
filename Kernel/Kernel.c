
#include <Common.h>
#include <Screen/Framebuffer.h>
#include <Screen/Output.h>
#include <ACPI.h>



void __attribute__((section(".entry"))) kernelInit(void) {
    screenInit();
    gdtInit();
    kprint("%bGDT initialized succesfully!\n", 0x57cc99);
    idtInit(); // KABUUMM
    kprint("%bIDT initialized succesfully!\n", 0x57cc99);
    acpiInit();
    kprint("%bParsed ACPI tables\n", 0x57cc99);
    sseInit();
    drawLine(200, 200, 250, 400, 0xffba00);
    drawLine(250, 400, 370, 400, 0xffba00);
    drawLine(370, 400, 200, 200, 0xffba00);

    __asm__ volatile("cli");
    for (;;) {
        __asm__ volatile("hlt");
    }

}