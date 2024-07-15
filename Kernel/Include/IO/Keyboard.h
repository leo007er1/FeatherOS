
#pragma once

#include <IO/Ports.h>

#define ps2Data 0x60
#define ps2Reg 0x64

void keyboardIsr();
void keyboardIrqHandler();
void keyboardInit();