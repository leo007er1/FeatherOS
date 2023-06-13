
#include <Common.h>
#include <Framebuffer.h>
#include <ACPI.h>



void __attribute__((section(".entry"))) kernelInit(void) {
    gdtInit();
    idtInit(); // KABUUMM
    screenInit();
    acpiInit();

    plotPixel(100, 10, 0xff00ff);
    plotPixel(101, 10, 0xff00ff);
    plotPixel(102, 10, 0xff00ff);
    plotPixel(103, 10, 0xff00ff);
    plotPixel(104, 10, 0xff00ff);
    plotPixel(105, 10, 0xff00ff);
    drawRectangle(100, 100, 220, 220, 0x457b9d);
    drawRectangle(800, 240, 150, 450, 0xccd5ae);

    __asm__ volatile("cli");
    for (;;) {
        __asm__ volatile("hlt");
    }

}