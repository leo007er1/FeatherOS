
#include <Utils/Strings.h>



char* IntToString(uint64_t num) {
    uint8_t i = 20;
    static char string[20];
    string[i] = 0; // You know, we should end a string

    while (num) {
        --i;
        string[i] = (num % 10) + 48; // 48 is "0" in ASCII
        num /= 10;
    }

    if (i == 20) {
        --i;
        string[i] = 48;
    }

    return &string[i];
}