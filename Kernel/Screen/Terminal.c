
#include <Common.h>
#include <Screen/Framebuffer.h>
#include <Screen/Terminal.h>


static uint32_t textColor = defaultTextColor;
static va_list* logArg;


void terminalInit(void) {
    drawBackground(defaultBackgroundColor);
}



int log(const char* string, ...) {
    // https://publications.gbdirect.co.uk/c_book/chapter9/stdarg.html
    va_list argList;
    va_start(argList, string);
    char currentChar;

    for (size_t stringPos = 0; string[stringPos]; ++stringPos) {
        currentChar = string[stringPos];

        if (posY == 1920) posY = 0;
        if (posX == 1080) {
            posY += fontCharHeight;
            posX = 0;
        }

        if (currentChar == 37) {
            logArg = &argList; // Pointer to current argument
            logFunc[string[stringPos + 1] - 97](); // Execute the function associated to a letter(c for char and so on)
            stringPos++;

            continue;
        }

        if (currentChar == 10) {
            posX = 0;
            posY += fontCharHeight;

            continue; // No need to draw \n

        } else if (currentChar == 9) {
            // TAB
            posX += fontCharWidth * 4;
            continue;
        }

        drawChar(currentChar, posX, posY, textColor);
        posX += fontCharWidth;
    }

    va_end(argList);
    textColor = defaultTextColor;
    return 0;
}

// These are functions for handling other log arguments when using %c and similar

void logChar(void) {
    char* arg = va_arg(*logArg, char*);
    drawChar(*arg, posX, posY, textColor);
    posX += fontCharWidth;
}

void logInt(void) {
    uint32_t currentColor = textColor;
    uint64_t* arg = va_arg(*logArg, uint64_t*);
    log(IntToString((uint64_t)arg));

    textColor = currentColor; // When recalling log the color gets changed to the default one
}

void logString(void) {
    char* arg = va_arg(*logArg, char*);
    log(arg);
}

void logColor(void) {
    uint32_t* arg = va_arg(*logArg, uint32_t*);
    textColor = (uint32_t)arg;
}

void logInvalid(void) {
    return;
}