#pragma once

#include <Common.h>
#include <Ports.h>
#include <Arch/x86/Pic.h>
#include <Screen/Terminal.h>


typedef struct {
    uint16_t offset0;
    uint16_t segSelector;
    uint8_t ist : 3; // Interrupt Stack Table offset
    uint8_t reserved0 : 5;
    uint8_t type : 4;
    uint8_t zero : 1;
    uint8_t dpl : 2;
    uint8_t present : 1;
    uint16_t offset1;
    uint32_t offset2;
    uint32_t reserved1;

} __attribute__((packed)) idtGate_t;


typedef struct {
    uint16_t limit;
    uint64_t address;

} __attribute__((packed)) idtr_t;


#define idtTrapGate 0xf
#define idtIntGate 0xe 
#define idtMaxGates 256

extern void setIdt();
extern void* intrList[];

void idtSetGate(void (*handler)(), uint16_t vector, uint8_t gateType, uint8_t gateDpl);
void idtInit(void);