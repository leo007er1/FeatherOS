#pragma once

#define idtIntFlags 0x8e
#define idtTrapFlags 0x8f


typedef struct {
    uint16_t address0;
    uint16_t segSelector; // Code segment selector in GDT
    uint8_t ist; // Bits 0 to 2 hold the Interrupt Stack Table offset, rest is 0
    uint8_t flags; // Gate type, Reserved, DPL and Present bit
    uint16_t address1;
    uint32_t address2;
    uint32_t zero;

} __attribute__((packed)) idtEntry_t;


typedef struct {
    uint16_t limit;
    uint64_t address;

} __attribute__((packed)) idtr_t;


#define kernelCs 0x08
#define idtEntries 256
static idtEntry_t idt[idtEntries];
idtr_t idtr;
extern void* interruptList[];

void idtInit(void);