#pragma once

#include <Screen/Terminal.h>

typedef struct {
    uint16_t limit0;
    uint16_t base0;
    uint8_t base1;
    uint8_t access; // Type field, Descriptor type, DPL and Segment present
    uint8_t limit1: 4;
    uint8_t flags: 4;
    uint8_t base2;
    uint32_t base3;
    uint32_t reserved;

} __attribute__((packed)) systemSegDesc_t;


typedef struct {
    // Base and limit are ignored in long mode
    uint16_t limit0;
    uint16_t base0;
    uint8_t base1;
    uint8_t access;
    uint8_t limit1 : 4;
    uint8_t flags : 4;
    uint8_t base2;

} __attribute__((packed)) gdtEntry_t;


typedef struct {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed)) gdtr_t;


#define gdtEntries 7
#define gdtKernelCode 0x08
#define gdtKernelData 0x10
#define gdtUserCode 0x18
#define gdtUserData 0x20
#define gdtKernelTss 0x28
#define gdtUserTss 0x30

void gdtInit(void);
extern void gdtReload();