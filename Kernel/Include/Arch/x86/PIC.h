
#pragma once

#define picCommandMaster 0x20
#define picDataMaster 0x21
#define picCommandSlave 0xa0
#define picDataSlave 0xa1

void picSendEoi(uint8_t irq);
void picDisable(void);