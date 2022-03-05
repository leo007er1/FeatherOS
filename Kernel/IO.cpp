#pragma once



void OutByte(unsigned short port, unsigned char value){
    // Assembly code. We use volatile to not allow GCC to mess up this piece of code
    asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));

}

unsigned char InByte(unsigned short port){
    unsigned char value;

    asm volatile("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}