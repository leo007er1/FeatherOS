
#include <Framebuffer.h>
#include <IbmVgaFont.h>


// *NOTES
// pitch = number of bytes per row
// bpp = bits per pixel


// See https://github.com/limine-bootloader/limine/blob/v4.x-branch/PROTOCOL.md
static volatile struct limine_framebuffer_request framebufferRequest = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};


static int charMask[8] = {128, 64, 32, 16, 8, 4, 2, 1};
static struct limine_framebuffer* framebuffer;
static uint32_t* framebufferBase;
static uint8_t bytesPerPixel;
static uint16_t pitch;

// Used for keeping track of text position
static uint16_t posX = 0;
static uint16_t posY = 0;



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


void printf(const uint8_t* string, uint32_t color) {
    for (size_t currentChar = 0; string[currentChar]; ++currentChar) {
        if (string[currentChar] == 10) {
            posX = 0;
            posY++;

            continue; // No need to draw \n
        }

        drawChar(string[currentChar], posX * fontCharWidth, posY * fontCharHeight, color);
        posX++;
    }
}


void drawChar(uint8_t charToDraw, uint64_t x, uint64_t y, uint32_t color) {
    uint8_t *c = ibmVga8x16 + (int32_t)(charToDraw * fontCharHeight);
    int mask[8] = {128, 64, 32, 16, 8, 4, 2, 1};

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
}