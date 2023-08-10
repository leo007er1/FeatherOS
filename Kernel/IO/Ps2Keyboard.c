
#include <Common.h>
#include <IO/Ps2Keyboard.h>
#include <Screen/Terminal.h>

// * NOTES
// https://wiki.osdev.org/%228042%22_PS/2_Controller
// https://wiki.osdev.org/Keyboard
// Keyboard is IRQ 1
// I/O ports:
// 0x60 -> data port
// 0x64(read) -> status register
// 0x64(write) -> command register


void keyboardIrqHandler() {
    uint8_t scancode = inPortB(ps2Data);
    print("Scancode: %c", scancode);
}


void keyboardInit() {
    // TODO: Check in FADT ACPI table if there are PS/2 controllers first!

    bool dualChannel = false;
    print("\nInitilizing PS/2 keyboard...\n");

    // Disable PS/2 ports
    outPortB(ps2Reg, 0xad);
    outPortB(ps2Reg, 0xa7);

    uint8_t garbageData = inPortB(ps2Data); // Flush output buffer

    // Disable scan code translation if enabled and IRQs
    outPortB(ps2Reg, 0x20);
    uint8_t configByte = inPortB(ps2Data);
    if (configByte << 6) configByte &= 0xbc; // Clear bit 0, 1 and 6
    outPortB(ps2Reg, ps2Data);
    outPortB(ps2Data, configByte);
    if (configByte << 5) dualChannel = true;

    // Test PS/2 controller
    outPortB(ps2Reg, 0xaa);
    if(inPortB(ps2Data) != 0x55) {
        print("%bPS/2 controller test failed!\n", 0xef233c);
        return;
    }

    // Check if it's a single channel controller or not
    if (dualChannel) {
        print("Dual channel PS/2 controller\n");
        outPortB(ps2Reg, 0xa8); // Enable second PS/2 port
        outPortB(ps2Reg, 0x20);
        configByte = inPortB(ps2Data);

        // If bit 5 is clear it's a dual channel controller
        if (!configByte << 5) {
            outPortB(ps2Reg, 0xa7);
            dualChannel = true;
        }
    }

    // Test ports
    outPortB(ps2Reg, 0xab);
    if (inPortB(ps2Data)) {
        print("%bPS/2 error: first port unavaiable!\n", 0xef233c);
        return;
    }
    if (dualChannel) {
        outPortB(ps2Reg, 0xa9);
        if (inPortB(ps2Data)) {
            print("%bPS/2 error: second port unavaiable!\n", 0xef233c);
            return;
        }
    }

    // Enable ports and IRQs
    outPortB(ps2Reg, 0xae);
    outPortB(ps2Reg, 0xa8);
    outPortB(ps2Reg, 0x20);
    configByte = inPortB(ps2Data);
    configByte |= 0x1;
    if (dualChannel) configByte |= 2;
    outPortB(ps2Reg, ps2Data);
    outPortB(ps2Data, configByte);
    
    print("%bPS/2 driver initialized succesfully!", 0x57cc99);
}