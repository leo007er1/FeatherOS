#include "../HeaderFiles/Common.h"
#include "../HeaderFiles/Utils/String.h"




unsigned int StringLenght(const char* string){
    unsigned int lenght = 0;

    for (lenght; string[lenght] != 0; lenght++);

    return lenght;
}



bool StringCompare(const char* string1, const char* string2){

    for (unsigned int i = 0; string1[i] || string2[i]; i++){
        if (string1[i] != string2[i]) return false;
    }

    // If we are here the strings are equal
    return true;
}