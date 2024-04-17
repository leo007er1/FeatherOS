#pragma once

#include <stdarg.h>
#include <Utils/Strings.h>

#define defaultTextColor 0xffffff
#define defaultBackgroundColor 0x000000

int log(const char* string, ...);
void logChar(void);
void logInt(void);
void logString(void);
void logColor(void);
void logInvalid(void);

static void (*logFunc[20])() = {
    logInvalid, logColor, logChar, logInt,
    logInvalid, logInvalid, logInvalid, logInvalid,
    logInvalid, logInvalid, logInvalid, logInvalid,
    logInvalid, logInvalid, logInvalid, logInvalid,
    logInvalid, logInvalid, logString, logInvalid
};