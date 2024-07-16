
#include <Arch/x86/Isr.h>
#include <Screen/Terminal.h>
#include <Screen/Framebuffer.h>
#include <IO/Keyboard.h>



static const char* exceptionsNames[] = {
    "Division by 0",
    "Debug exception",
    "Non-maskable interrupt exception",
    "Breakpoint exception",
    "Overflow",
    "Bound range exceeded",
    "Invalid opcode",
    "Device not avaiable",
    "Double fault",
    "Coprocessor segment overrun",
    "Invalid TSS",
    "Segment not present",
    "Stack-segment fault",
    "General protection fault",
    "Page fault",
    "Reserved exception",
    "x87 floating-point exception",
    "Alignment check",
    "Machine check",
    "SIMD floating-point exception",
    "Virtualization exception",
    "Control protection exception",
    "Reserved exception",
    "Reserved exception",
    "Reserved exception",
    "Reserved exception",
    "Reserved exception",
    "Reserved exception",
    "Hypervisor injection exception",
    "VMM communication exception",
    "Security exception",
    "Reserved exception"
};


void generalIsrHandler(cpuStatus_t* cpuStatus) {
    clearScreen(0x000000);

    log(R"(
                            ...
                            ;::::;
                        ;::::; :;
                        ;:::::'   :;
                        ;:::::;     ;.
                    ,:::::'       ;           OOO\
                    ::::::;       ;          OOOOO\
                    ;:::::;       ;         OOOOOOOO
                    ,;::::::;     ;'         / OOOOOOO
                    ;:::::::::`. ,,,;.        /  / DOOOOOO
                .';:::::::::::::::::;,     /  /     DOOOO
                ,::::::;::::::;;;;::::;,   /  /        DOOO
                ;`::::::`'::::::;;;::::: ,#/  /          DOOO
                :`:::::::`;::::::;;::: ;::#  /            DOOO
                ::`:::::::`;:::::::: ;::::# /              DOO
                `:`:::::::`;:::::: ;::::::#/               DOO
                :::`:::::::`;; ;:::::::::##                OO
                ::::`:::::::`;::::::::;:::#                OO
                `:::::`::::::::::::;'`:;::#                O 
                `:::::`::::::::;' /  / `:#                  
                ::::::`:::::;'  /  /   `#
                %b%s
                Interrupt code: %d%b
                
                The %bmagic reaper%b just destroyed FeatherOS!
                %bKill him by restarting the computer!)", 0xef233c, exceptionsNames[cpuStatus->isrNumber], cpuStatus->isrNumber, 0xffffff, 0x8338ec, 0xffffff, 0x57cc99);


    __asm__ volatile("cli");
    for (;;) __asm__ volatile("hlt");
}



void generalIrqHandler(cpuStatus_t* cpuStatus) {
    if (cpuStatus->isrCode == 1) {
        keyboardIsr();
        outb(0x20, 0x20);

    } else if (cpuStatus->isrCode >= 2) {
        log("\n%bUnhandled IRQ %d!", 0xef233c, cpuStatus->isrNumber);

        __asm__ volatile("cli");
        for (;;) __asm__ volatile("hlt");
    
    }
}