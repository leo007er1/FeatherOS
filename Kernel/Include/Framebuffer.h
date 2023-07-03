#pragma once

#include <Common.h>
#include <limine.h>


// Font is 8x16, so 16 bytes per character
#define fontCharWidth 8
#define fontCharHeight 16


void plotPixel(uint64_t x, uint64_t y, uint32_t color);
void drawRectangle(uint64_t x, uint64_t y, uint32_t width, uint32_t height, uint32_t color);
void drawBackground(uint32_t color);
void drawChar(uint8_t charToDraw, uint64_t x, uint64_t y, uint32_t color);
void printf(const uint8_t* string, uint32_t color);
void screenInit(void);