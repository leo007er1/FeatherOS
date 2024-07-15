
#include <Common.h>
#include <IO/Ports.h>


uint8_t inb(uint16_t port) {
    uint8_t input;
    __asm__ volatile("in %%dx, %%al" : "=a" (input) : "d" (port));

    return input;
}

void outb(uint16_t port, uint8_t byte) {
    __asm__ volatile("out %%al, %%dx" : : "a" (byte), "d" (port));
}

uint16_t inw(uint16_t port) {
    uint16_t input;
    __asm__ volatile("in %%dx, %%ax" : "=a" (input) : "d" (port));

    return input;
}

void outw(uint16_t port, uint16_t word) {
    __asm__ volatile("out %%ax, %%dx" : : "a"(word), "d" (port));
}


void ioWait(void) {
    outb(0x80, 0);
}