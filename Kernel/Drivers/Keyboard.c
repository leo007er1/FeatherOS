
#include <Common.h>
#include <Drivers/Keyboard.h>
#include <Screen/Terminal.h>

// * NOTES
// https://osdev.wiki/wiki/%228042%22_PS/2_Controller
// https://osdev.wiki/wiki/PS/2_Keyboard
// Keyboard is IRQ 1
// I/O ports:
// 0x60 -> data port
// 0x64(read) -> status register
// 0x64(write) -> command register


void keyboardIsr() {
    // uint8_t scancode = inb(0x60);

    // log("Scancode: %c", scancode);
    log("ciao");
}


void keyboardInit() {
    // TODO: Check in FADT ACPI table if there are PS/2 controllers first!

    log("\nInitializing PS/2 keyboard driver...\n");
    // uint8_t controllerConfig;
    // bool dualChannel = false;

    // // Disable PS/2 devices
    // outb(ps2Data, 0xad);
    // outb(ps2Data, 0xa7);

    // uint8_t garbageData = inb(ps2Data); // Flush output buffer

    // // Disable IRQs and translations
    // outb(ps2Reg, 0x20);
    // if (inb(ps2Reg) << 0) {
    //     controllerConfig = inb(ps2Data);
    //     controllerConfig &= 0xbc; // Clears bit 0, 1, 6
    // }
    // outb(ps2Reg, 0x60);
    // outb(ps2Data, controllerConfig);

    // // Controller self test
    // outb(ps2Reg, 0xaa);
    // if (inb(ps2Data) != 0x55) {
    //     log("%bPS/2 controller test failed!\n", 0xef233c);
    //     return;
    // }

    // // Check if we have 2 channels
    // outb(ps2Reg, 0xa8);
    // outb(ps2Reg, 0x20);
    // if (inb(ps2Reg) << 0) {
    //     controllerConfig = inb(ps2Data);

    //     if (!controllerConfig << 5) {
    //         log("Dual channel PS/2 controller\n");
    //         dualChannel = true;
    //         outb(ps2Reg, 0xa7);

    //         controllerConfig &= 0x2;
    //         outb(ps2Reg, 0x60);
    //         outb(ps2Data, controllerConfig);
    //     }
    // }

    // // Test first port
    // outb(ps2Reg, 0xab);
    // if (inb(ps2Data) != 0) {
    //     log("First PS/2 port test error!\n");
    // }

    // if (dualChannel) {
    //     // Test second port
    //     outb(ps2Reg, 0xa9);
    //     if (inb(ps2Data) != 0) log("Second PS/2 port test error!\n");
    // }

    // // Enable ports
    // outb(ps2Reg, 0xae);
    // if (dualChannel) outb(ps2Reg, 0xa8);

    // // Enable interrupts
    // outb(ps2Reg, 0x20);
    // if (inb(ps2Reg) << 0) {
    //     controllerConfig = inb(ps2Data);

    //     if (dualChannel) {
    //         controllerConfig |= 0x3;
    //     } else {
    //         controllerConfig |= 0x1;
    //     }

    //     outb(ps2Reg, 0x60);
    //     outb(ps2Data, controllerConfig);
    // }

    // Reset connect devices
    // outb();

    // // Reset keyboard
    // if (!inb(ps2Reg) & 0x02) {
    //     outb(ps2Data, 0xFF);
    //     log("%Keyboard reset command sent\n", 0x57cc99);

    //     if (inb(ps2Reg) & 0x01) {
    //         if (inb(ps2Data) == 0xFA) log("%bKeyboard: command acknoweldeged\n", 0x57cc99);
    //     }
    // }

    // Tell PIC not to mask IRQ 1(keyboard)
    // uint8_t currentMask = inb(0x21);
    // outb(0x21, currentMask & 0xfd);

    log("[ %bOK%b ] Keyboard initialized succesfully!\n", 0x57cc99, 0xffffff);
}