
#include <Arch/x86/Pic.h>
#include <Screen/Terminal.h>


void picSendEoi(uint8_t irq) {
    if (irq >= 8) outb(0xa0, 0x20);
    outb(0x20, 0x20);
}


void picRemap(void) {
    // ICW1
    outb(0x20, 0x11);
    ioWait();
    outb(0xa0, 0x11);
    ioWait();

    // ICW2
    outb(0x21, 0x20); // IRQ 0 to 7
    ioWait();
    outb(0xa1, 0x28); // IRQ 8 to 15
    ioWait();

    // ICW3
    outb(0x21, 0x04); // Slave PIC at IRQ 2
    ioWait();
    outb(0xa1, 0x02); // Cascade identity
    ioWait();

    // ICW4
    outb(0x21, 0x01); // 8086 mode pls, not 8080
    ioWait();
    outb(0xa1, 0x01);
    ioWait();

    // Mask all interrupts
    outb(0x21, 0xfd);
    ioWait();
    outb(0xa1, 0xff);
    ioWait();

    log("%bRemapped PIC!\n", 0x57cc99);
}