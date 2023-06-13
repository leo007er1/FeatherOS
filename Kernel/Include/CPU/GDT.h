#pragma once


typedef struct {
    uint16_t limit0; // Size of segment
    uint16_t base0;
    uint8_t base1;
    uint8_t access; // Type field, Descriptor type, DPL and Segment present
    uint8_t limit1: 4;
    uint8_t flags: 4;
    uint8_t base2;

} __attribute__((packed)) gdtSeg_t;


typedef struct {
    uint16_t limit;
    uint64_t address;
} __attribute__((packed)) gdtr_t;


void gdtInit(void);