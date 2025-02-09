
#pragma once

#include <Common.h>
#include <Ports.h>

#define pic1Command 0x20
#define pic1Data 0x21
#define pic2Command 0xa0
#define pic2Data 0xa1

void picSendEoi(uint64_t isr);
void picRemap(void);