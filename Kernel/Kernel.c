
#include <Common.h>
#include <Screen/Framebuffer.h>
#include <Screen/Terminal.h>
#include <Arch/x86/Gdt.h>
#include <Arch/x86/Idt.h>
#include <Arch/x86/Acpi.h>
#include <IO/Ps2Keyboard.h>
#include <Memory/Pmm.h>

extern void sseInit();


void __attribute__((section(".entry"))) kernelInit(void) {
    screenInit();
    terminalInit();
    gdtInit();
    log("%bGDT initialized succesfully!\n", 0x57cc99);
    idtInit(); // KABUUMM
    log("%bIDT initialized succesfully!\n", 0x57cc99);
    acpiInit();
    log("%bParsed ACPI tables\n", 0x57cc99);
    sseInit();
    log("%bMemory size: %dMB\n", 0x57cc99, (uint64_t)(GetMemorySize() / 1048576));

    keyboardInit();

    drawLine(300, 200, 250, 450, 0xffba00);
    drawLine(250, 450, 350, 450, 0xffba00);
    drawLine(350, 450, 300, 200, 0xffba00);

    __asm__ volatile("cli");
    for (;;) {
        __asm__ volatile("hlt");
    }

}