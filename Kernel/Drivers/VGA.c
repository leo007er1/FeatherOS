#include "../HeaderFiles/Common.h"
#include "../HeaderFiles/IO.h"
#include "../HeaderFiles/Drivers/VGA.h"


struct vgaStruct vga;



void VgaSetCursor(unsigned short position){
    OutByte(0x3D4, 0x0F);  // Tells VGA board we are setting the low cursor byte
    OutByte(0x3D5, (unsigned char)(position & 0xFF));
    OutByte(0x3D4, 0x0E);  // Tells VGA board we are setting the hight cursor byte
    OutByte(0x3D5, (unsigned char)((position >> 8) & 0xFF));

    vga.cursorPosition = position;
}


// Returns a position in vga from x and y coordinates
unsigned short VgaCoordinates(unsigned short x, unsigned short y){
    return x + (VgaWidth * y);
}


void VgaPrint(const char* string){
    unsigned short cursorPos = vga.cursorPosition;

    for (unsigned short i = 0; string[i] != 0; i++){
        if (string[i] == 10){
            // New line char
            cursorPos += VgaWidth + (cursorPos % VgaWidth);
        } else if(string[i] == 13){
            // Carriage return char
            cursorPos += cursorPos % VgaWidth;
        }

        *(vga.memory + cursorPos * 2) = string[i];

        cursorPos++;
    }

    VgaSetCursor(cursorPos);
}


void VgaInit(){
    vga.cursorPosition = 0;
    vga.memory = (unsigned short*)0xb8000;
    vga.memorySize = 2000 * sizeof(unsigned short);
    
}