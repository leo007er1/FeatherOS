#include "HeaderFiles/Common.h"
#include "HeaderFiles/Drivers/VGA.h"


// Our include binary ASCII title
extern const char VgaOsTitle[];


extern void KernelInit(){
    VgaInit();
    // VgaSetCursor(2);

    return;
}