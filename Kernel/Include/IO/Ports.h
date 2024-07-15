#pragma once


uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t byte);
uint16_t inw(uint16_t port);
void outw(uint16_t port, uint16_t word);
void ioWait(void);