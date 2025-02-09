
#include <Common.h>
#include <Screen/Framebuffer.h>
#include <Screen/Terminal.h>
#include <Arch/x86/Gdt.h>
#include <Arch/x86/Idt.h>
#include <Arch/x86/Acpi.h>
#include <Drivers/Keyboard.h>
#include <Memory/Pmm.h>

extern void sseInit();


static volatile struct limine_boot_time_request bootTimeRequest = {
    .id = LIMINE_BOOT_TIME_REQUEST,
    .revision = 0
};


void __attribute__((section(".entry"))) kernelInit(void) {
    screenInit();

    log("Time since UNIX time: %d seconds\n\n", (uint64_t)bootTimeRequest.response->boot_time);

    gdtInit();
    idtInit(); // KABUUMM
    acpiInit();
    log("[ %bOK%b ] Parsed ACPI tables!\n", 0x57cc99, 0xffffff);
    sseInit();
    keyboardInit();

    log("%bMemory size: %dMB\n", 0x57cc99, (uint64_t)(GetMemorySize() / 1048576));
    terminalInit();

    // float g = 5 / 0;

    __asm__ volatile("int $0x21");

    __asm__ volatile("cli");
    for (;;) __asm__ volatile("hlt");

}