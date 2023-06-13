
#include <Framebuffer.h>


// *NOTES
// pitch = number of bytes per row
// bpp = bits per pixel


// See https://github.com/limine-bootloader/limine/blob/v4.x-branch/PROTOCOL.md
static volatile struct limine_framebuffer_request framebufferRequest = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};


static struct limine_framebuffer* framebuffer;
static uint32_t* framebufferBase;
static uint8_t bytesPerPixel;
static uint16_t pitch;


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



void screenInit(void) {
    // Get the first framebuffer
    framebuffer = framebufferRequest.response->framebuffers[0];
    framebufferBase = framebuffer->address;
    bytesPerPixel = framebuffer->bpp / 32;
    pitch = framebuffer->pitch / 4;
}