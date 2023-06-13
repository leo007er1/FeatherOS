#pragma once


typedef struct {
    uint16_t address0;
    uint16_t segSelector; // Code segment selector in GDT
    uint8_t ist;
    uint8_t flags; // Gate type, Reserved, DPL and Present bit
    uint16_t address1;
    uint32_t address2;
    uint32_t zero;

} __attribute__((packed)) idtEntry_t;


typedef struct {
    uint16_t limit;
    uint64_t address;

} __attribute__((packed)) idtr_t;


void idtInit(void);