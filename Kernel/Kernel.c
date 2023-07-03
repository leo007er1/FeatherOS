
#include <Common.h>
#include <Framebuffer.h>
#include <ACPI.h>



void __attribute__((section(".entry"))) kernelInit(void) {
    gdtInit();
    screenInit();
    printf("GDT initialized succesfully!\n", 0x59cd90);
    idtInit(); // KABUUMM
    printf("IDT initialized succesfully!\n", 0x59cd90);
    acpiInit();
    printf("Parsed ACPI tables\n", 0x59cd90);

    drawRectangle(0, 100, 220, 220, 0x457b9d);
    drawRectangle(800, 240, 150, 450, 0xccd5ae);
    printf("\n\nCiao mamma!", 0xffffff);
    printf("\nOOOooh nuova riga\nNON SI E' ROTTO SSSSEEE", 0xffffff);

    __asm__ volatile("cli");
    for (;;) {
        __asm__ volatile("hlt");
    }

}