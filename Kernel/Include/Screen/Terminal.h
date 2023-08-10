#pragma once

#include <stdarg.h>

#define defaultTextColor 0xffffff

int print(const char* string, ...);
void printChar(void);
void printString(void);
void printColor(void);
void printInvalid(void);

static void (*printFunc[20])() = {
    printInvalid, printColor, printChar, printInvalid,
    printInvalid, printInvalid, printInvalid, printInvalid,
    printInvalid, printInvalid, printInvalid, printInvalid,
    printInvalid, printInvalid, printInvalid, printInvalid,
    printInvalid, printInvalid, printString, printInvalid
};