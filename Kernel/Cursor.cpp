#pragma once

#include "IO.cpp"

#define VGA_Memory (unsigned char*) 0xb8000
#define VGA_Width 80


unsigned short cursorPosition;


void SetCursorPosition(unsigned short position){
    OutByte(0x3D4, 0x0F);
    OutByte(0x3D5, (unsigned char)(position & 0xFF));
    OutByte(0x3D4, 0x0E);
    OutByte(0x3D5, (unsigned char)((position >> 8) & 0xFF));

    cursorPosition = position;
}


unsigned short CursorPositionFromIndex(unsigned char x, unsigned char y){
    return y * VGA_Width + x;
}