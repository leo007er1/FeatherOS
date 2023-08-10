
#include <Common.h>
#include <Screen/Framebuffer.h>
#include <Screen/Terminal.h>


static uint32_t textColor = defaultTextColor;
static va_list* printArg;


// int vfprintf(void* stream, va_list va, ...) {
    // 
// }


int print(const char* string, ...) {
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
            printArg = &argList; // Pointer to current argument
            printFunc[string[stringPos + 1] - 97](); // Execute the function associated to a letter(c for char and so on)
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

// These are functions for handling other print arguments when using %c and similar

void printChar(void) {
    char* arg = va_arg(*printArg, char*);
    drawChar(*arg, posX, posY, textColor);
    posX += fontCharWidth;
}

void printString(void) {
    char* arg = va_arg(*printArg, char*);
    print(arg);
}

void printColor(void) {
    uint32_t* arg = va_arg(*printArg, uint32_t*);
    textColor = arg;
}

void printInvalid(void) {
    return;
}