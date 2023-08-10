
#include <Common.h>
#include <IO/Ports.h>


uint8_t inPortB(uint16_t port) {
    uint8_t input;
    __asm__ volatile("in %%dx, %%al" : "=a" (input) : "d" (port));

    return input;
}

void outPortB(uint16_t port, uint8_t byte) {
    __asm__ volatile("out %%al, %%dx" : : "a" (byte), "d" (port));
}