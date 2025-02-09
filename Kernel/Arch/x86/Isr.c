
#include <Arch/x86/Isr.h>


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


void __attribute__((noreturn)) intHandler(intFrame_t* intFrame) {
    __asm__ volatile("cli");

    if (intFrame->isrNum <= 31) {
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
                    %bKill him by restarting the computer!)", 0xef233c, exceptionsNames[intFrame->isrNum], intFrame->isrNum, 0xffffff, 0x8338ec, 0xffffff, 0x57cc99);


        for (;;) __asm__ volatile("hlt");
    } else {

        log("Fired interrupt %d\n", intFrame->isrNum);
        picSendEoi(intFrame->isrNum);
    }

    __asm__ volatile("sti");
}
