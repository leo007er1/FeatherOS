
#include <Screen/Framebuffer.h>
#include <Screen/IbmVgaFont.h>


// *NOTES
// pitch = number of bytes per row
// bpp = bits per pixel


// See https://github.com/limine-bootloader/limine/blob/v4.x-branch/PROTOCOL.md
static volatile struct limine_framebuffer_request framebufferRequest = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};



void plotPixel(uint64_t x, uint64_t y, uint32_t color) {
    framebufferBase[(x * bytesPerPixel) + (y * pitch)] = color;
}


void drawRectangle(uint64_t x, uint64_t y, uint32_t width, uint32_t height, uint32_t color) {
    for (size_t i = 0; i < width; i++) {
        for (size_t k = 0; k < height; k++) {
            framebufferBase[((x + i) * bytesPerPixel) + ((y + k) * pitch)] = color;
        }
    }
}


void drawBackground(uint32_t color) {
    for (size_t i = 0; i < (framebuffer->width * framebuffer->height); i++) {
        framebufferBase[i] = color;
    }
}


void drawChar(char charToDraw, uint64_t x, uint64_t y, uint32_t color) {
    char* c = ibmVga8x16 + (int32_t)(charToDraw * fontCharHeight);

    for (uint16_t charY = 0; charY < fontCharHeight; charY++) {
        for (uint16_t charX = 0; charX < fontCharWidth; charX++) {
            if (c[charY] & charMask[charX]) plotPixel(x + charX, y + charY, color);
        }
    }
}


void screenInit(void) {
    // Get the first framebuffer
    framebuffer = framebufferRequest.response->framebuffers[0];
    framebufferBase = framebuffer->address;
    bytesPerPixel = framebuffer->bpp / 32;
    pitch = framebuffer->pitch / 4;
    framebufferInfo[0] = framebuffer->width;
    framebufferInfo[1] = framebuffer->height;

    drawBackground(0x2b2d42);
}