#pragma once

#include <Common.h>
#include <limine.h>


// Font is 8x16, so 16 bytes per character
#define fontCharWidth 8
#define fontCharHeight 16

static const int charMask[8] = {128, 64, 32, 16, 8, 4, 2, 1};
static struct limine_framebuffer* framebuffer;
static uint32_t* framebufferBase;
static uint8_t bytesPerPixel;
static uint16_t pitch;
static uint64_t framebufferInfo[2];

// Used for keeping track of text position
static uint16_t posX = 0;
static uint16_t posY = 0;



void plotPixel(uint64_t x, uint64_t y, uint32_t color);
void drawRectangle(uint64_t x, uint64_t y, uint32_t width, uint32_t height, uint32_t color);
void drawBackground(uint32_t color);
void drawChar(char charToDraw, uint64_t x, uint64_t y, uint32_t color);
void screenInit(void);