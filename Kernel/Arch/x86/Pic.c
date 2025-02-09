
#include <Arch/x86/Pic.h>
#include <Screen/Terminal.h>


void picSendEoi(uint64_t isr) {
    if (isr <= 40) outb(pic2Command, 0x20);
    outb(0x20, 0x20);
}


void picRemap(void) {
    // ICW1
    outb(pic1Command, 0x11);
    ioWait();
    outb(pic2Command, 0x11);
    ioWait();

    // ICW2
    outb(pic1Data, 0x20); // IRQ 0 to 7
    ioWait();
    outb(pic2Data, 0x28); // IRQ 8 to 15
    ioWait();

    // ICW3
    outb(pic1Data, 0x04); // Slave PIC at IRQ 2
    ioWait();
    outb(pic2Data, 0x02); // Cascade identity
    ioWait();

    // ICW4
    outb(pic1Data, 0x01); // 8086 mode pls, not 8080
    ioWait();
    outb(pic2Data, 0x01);
    ioWait();

    // Mask all interrupts
    outb(pic1Data, 0xfd);
    ioWait();
    outb(pic2Data, 0xff);
    ioWait();

    log("[ %bOK%b ] Remapped PIC!\n", 0x57cc99, 0xffffff);
}