
#pragma once

#include <Common.h>
#include <Arch/x86/Pic.h>
#include <Screen/Terminal.h>
#include <Screen/Framebuffer.h>


// Used to check the values pushed to the stack from the ISR handlers
typedef __attribute__((packed)) struct {
    uint64_t cr4, cr3, cr2, cr0;
    uint64_t r15, r14, r13, r12, r11, r10, r9, r8;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t rbp;
    uint64_t rdx;
    uint64_t rcx;
    uint64_t rbx;
    uint64_t rax;

    // Values we pushed in the macros
    uint64_t isrNum;
    uint64_t isrCode;

    // Stuff popped by iretq
    uint64_t rip;
    uint64_t cs;
    uint64_t flags;
    uint64_t rsp;
    uint64_t ss;
    
} __attribute__((packed)) intFrame_t;


void __attribute__((noreturn)) intHandler(intFrame_t* intFrame);
void generalIrqHandler(intFrame_t* intFrame);