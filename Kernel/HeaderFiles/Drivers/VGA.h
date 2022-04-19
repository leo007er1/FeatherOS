#ifndef VGAHeader
#define VGAHeader


struct vgaStruct{
    unsigned short cursorPosition;
    unsigned short* memory;
    unsigned short memorySize;

};


#define VgaWidth 25
#define VgaHeight 80


void VgaInit();
void VgaSetCursor(unsigned short position);
unsigned short VgaCoordinates(unsigned short x, unsigned short y);
void VgaPrint(const char* string);

#endif