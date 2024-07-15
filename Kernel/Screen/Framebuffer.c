
#include <Screen/Framebuffer.h>
#include <Screen/IbmVgaFont.h>


// *NOTES
// pitch = number of bytes per row
// bpp = bits per pixel


static volatile struct limine_framebuffer_request framebufferRequest = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};



void plotPixel(uint32_t x, uint32_t y, uint32_t color) {
    framebufferBase[(x * bytesPerPixel) + (y * pitch)] = color;
}


// https://github.com/ssloy/tinyrenderer/wiki/Lesson-1:-Bresenham%E2%80%99s-Line-Drawing-Algorithm
void drawLine(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color) {
    bool steep = false;

    if (abs(x0 - x1) < abs(y0 - y1)) {
        steep = true;
        uint32_t temp = x0;
        x0 = y0;
        y0 = temp;
        temp = x1;
        x1 = y1;
        y1 = temp;
    }

    if (x0 > x1) {
        uint32_t temp = x0;
        x0 = x1;
        x1 = temp;
        temp = y0;
        y0 = y1;
        y1 = temp;
    }

    int dx = x1 - x0;
    int dy = y1 - y0;
    int derror2 = abs(dy) * 2;
    int error2 = 0;
    int y = y0;

    for (uint32_t x = x0; x <= x1; x++) {
        if (steep) {
            plotPixel(y, x, color);
        } else {
            plotPixel(x, y, color);
        }

        error2 += derror2;
        if (error2 > dx) {
            y += (y1 > y0 ? 1 : -1); 
            error2 -= dx * 2;
        }
    }
}


void drawRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t color) {
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


void drawChar(char charToDraw, uint32_t x, uint32_t y, uint32_t color) {
    char* c = ibmVga8x16 + (int32_t)(charToDraw * fontCharHeight);

    for (uint16_t charY = 0; charY < fontCharHeight; charY++) {
        for (uint16_t charX = 0; charX < fontCharWidth; charX++) {
            if (c[charY] & charMask[charX]) plotPixel(x + charX, y + charY, color);
        }
    }
}


void clearScreen(uint32_t color) {
    for (size_t i = 0; i < (framebuffer->width * framebuffer->height); i++) {
        framebufferBase[i] = color;
    }

    posX = 0;
    posY = 0;
}


void screenInit(void) {
    // Get the first framebuffer
    framebuffer = framebufferRequest.response->framebuffers[0];
    framebufferBase = framebuffer->address;
    bytesPerPixel = framebuffer->bpp / 32;
    pitch = framebuffer->pitch / 4;
    framebufferInfo[0] = framebuffer->width;
    framebufferInfo[1] = framebuffer->height;

    drawBackground(0x000000);
}