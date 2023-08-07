
#include <Common.h>
#include <Screen/Framebuffer.h>
#include <Screen/Output.h>


static uint32_t textColor = defaultTextColor;
static va_list* kprintArg;


void kprint(const char* string, ...) {
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
            kprintArg = &argList; // Pointer to current argument
            kprintFunc[string[stringPos + 1] - 97](); // Execute the function associated to a letter(c for char and so on)
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
}

// These are functions for handling other kprint arguments when using %c and similar

void kprintChar(void) {
    char* arg = va_arg(*kprintArg, char*);
    drawChar(*arg, posX, posY, textColor);
    posX += fontCharWidth;
}

void kprintColor(void) {
    uint32_t* arg = va_arg(*kprintArg, uint32_t*);
    textColor = arg;
}

void kprintInvalid(void) {
    return;
}