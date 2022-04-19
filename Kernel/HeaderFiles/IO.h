#ifndef IOHeader
#define IOHeader


void OutByte(unsigned short port, unsigned char value);
unsigned char InByte(unsigned short port);
void OutWord(unsigned short port, unsigned short value);
unsigned short InWord(unsigned short port);

#endif