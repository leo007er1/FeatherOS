#include "HeaderFiles/Common.h"
#include "HeaderFiles/IO.h"




void OutByte(unsigned short port, unsigned char value){
    asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}


unsigned char InByte(unsigned short port){
    unsigned char valueToReturn;

    asm volatile("inb %1, %0" : "=a"(valueToReturn) : "Nd"(port));

    return valueToReturn;
}


void OutWord(unsigned short port, unsigned short value){
    asm volatile("outw %0, %1" : : "a"(value), "Nd"(port));
}


unsigned short InWord(unsigned short port){
    unsigned short valueToReturn;

    asm volatile("inw %1, %0" : "=a"(valueToReturn) : "Nd"(port));

    return valueToReturn;
}