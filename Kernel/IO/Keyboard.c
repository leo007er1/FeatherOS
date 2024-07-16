
#include <Common.h>
#include <IO/Keyboard.h>
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
    uint8_t data = inb(ps2Data);
    log("Scancode!\n");
    // uint8_t status = inb(ps2Reg);

    // if (status & 0x01) {
    //     uint8_t scancode = inb(ps2Data);

    //     log("Scancode: %c", scancode);
    // }
}


void keyboardInit() {
    // TODO: Check in FADT ACPI table if there are PS/2 controllers first!

    // bool dualChannel = false;
    // log("\nInitilizing PS/2 keyboard...\n");

    // // Disable PS/2 ports
    // outb(ps2Reg, 0xad);
    // outb(ps2Reg, 0xa7);

    // uint8_t garbageData = inb(ps2Data); // Flush output buffer

    // // Disable scan code translation if enabled and IRQs
    // outb(ps2Reg, 0x20);
    // uint8_t configByte = inb(ps2Data);
    // if (configByte << 6) configByte &= 0xbc; // Clear bit 0, 1 and 6
    // outb(ps2Reg, 0x60);
    // outb(ps2Data, configByte);
    // if (configByte << 5) dualChannel = true;

    // // Test PS/2 controller
    // outb(ps2Reg, 0xaa);
    // if(inb(ps2Data) != 0x55) {
    //     log("%bPS/2 controller test failed!\n", 0xef233c);
    //     return;
    // }

    // // Check if it's a single channel controller or not
    // if (dualChannel) {
    //     log("Dual channel PS/2 controller\n");
    //     outb(ps2Reg, 0xa8); // Enable second PS/2 port
    //     outb(ps2Reg, 0x20);
    //     configByte = inb(ps2Data);

    //     // If bit 5 is clear it's a dual channel controller
    //     if (!configByte << 5) {
    //         outb(ps2Reg, 0xa7);
    //         dualChannel = true;
    //     }
    // }

    // // Test ports
    // outb(ps2Reg, 0xab);
    // if (inb(ps2Data)) {
    //     log("%bPS/2 error: first port unavaiable!\n", 0xef233c);
    //     return;
    // }
    // if (dualChannel) {
    //     outb(ps2Reg, 0xa9);
    //     if (inb(ps2Data)) {
    //         log("%bPS/2 error: second port unavaiable!\n", 0xef233c);
    //         return;
    //     }
    // }

    // // Enable ports and IRQs
    // outb(ps2Reg, 0xae);
    // outb(ps2Reg, 0xa8);
    // outb(ps2Reg, 0x20);
    // configByte = inb(ps2Data);
    // configByte |= 0x1;
    // if (dualChannel) configByte |= 0x3;
    // outb(ps2Reg, 0x60);
    // outb(ps2Data, configByte);

    // // Reset keyboard
    // if (!inb(ps2Reg) & 0x02) {
    //     outb(ps2Data, 0xFF);
    //     log("%Keyboard reset command sent\n", 0x57cc99);

    //     if (inb(ps2Reg) & 0x01) {
    //         if (inb(ps2Data) == 0xFA) log("%bKeyboard: command acknoweldeged\n", 0x57cc99);
    //     }
    // }

    // Tell PIC not to mask IRQ 1(keyboard)
    uint8_t currentMask = inb(0x21);
    outb(0x21, currentMask & 0xfd);

    uint8_t garbageData = inb(ps2Data); // Flush output buffer

    log("%bKeyboard initialized succesfully!", 0x57cc99);
}