#pragma once

#include <Common.h>
#include <limine.h>



void plotPixel(uint64_t x, uint64_t y, uint32_t color);
void drawRectangle(uint64_t x, uint64_t y, uint32_t width, uint32_t height, uint32_t color);
void screenInit(void);