
#include <Common.h>
#include <IO/Ports.h>
#include <Arch/x86/PIC.h>




void picSendEoi(uint8_t irq) {
    if (irq >= 8) {
        outPortB(picCommandSlave, 0x20);
        return;
    }

    outPortB(picCommandMaster, 0x20);
}


void picDisable(void) {
    // Send ICWs and remap IRQs
    outPortB(picCommandMaster, 0x11);
    outPortB(picCommandSlave, 0x11);
    outPortB(picDataMaster, 0x20); // IRQ 0 to 7
    outPortB(picDataSlave, 0x28); // IRQ 8 to 15
    outPortB(picDataMaster, 0x4); // Master IRQ pin 2 is connected to slave
    outPortB(picDataSlave, 0x2);
    outPortB(picDataMaster, 0x1); // 8086 mode pls, not 8080
    outPortB(picDataSlave, 0x1);

    // Mask all IRQs
    outPortB(picDataMaster, 0xff);
    outPortB(picDataSlave, 0xff);
}
