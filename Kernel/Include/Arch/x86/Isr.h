
#pragma once

#include <Common.h>


// Used to check the values pushed to the stack from the ISR handlers
typedef struct {
    uint64_t r15;
    uint64_t r14;
    uint64_t r13;
    uint64_t r12;
    uint64_t r11;
    uint64_t r10;
    uint64_t r9;
    uint64_t r8;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t rbp;
    uint64_t rdx;
    uint64_t rcx;
    uint64_t rbx;
    uint64_t rax;

    // Values we pushed before jumping to isrCommonHandler
    uint64_t isrNumber;
    uint64_t isrCode;

    // Stuff popped by iretq
    uint64_t rip;
    uint64_t cs;
    uint64_t flags;
    uint64_t rsp;
    uint64_t ss;
    
} __attribute__((packed)) cpuStatus_t;


void generalIsrHandler(cpuStatus_t* cpuStatus);
void generalIrqHandler(cpuStatus_t* cpuStatus);