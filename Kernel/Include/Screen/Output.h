#pragma once

#include <stdarg.h>

#define defaultTextColor 0xffffff

void kprint(const char* string, ...);
void kprintChar(void);
void kprintColor(void);
void kprintInvalid(void);

static void (*kprintFunc[4])() = {
    kprintInvalid, kprintColor, kprintChar,
    kprintInvalid
};