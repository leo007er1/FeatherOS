#include "Cursor.cpp"


extern "C" void kernel_start(){
    SetCursorPosition(CursorPositionFromIndex(0, 0));
    return;
}