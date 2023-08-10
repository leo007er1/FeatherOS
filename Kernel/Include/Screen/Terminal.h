#pragma once

#include <stdarg.h>

#define defaultTextColor 0xffffff

int print(const char* string, ...);
void printChar(void);
void printColor(void);
void printInvalid(void);

static void (*printFunc[4])() = {
    printInvalid, printColor, printChar,
    printInvalid
};