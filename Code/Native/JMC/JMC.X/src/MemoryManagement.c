#include "MemoryManagement.h"

unsigned char Mm_GetByteNVM(unsigned char *byte)
{
    return *byte;
}

void Mm_SetByteNVM(unsigned char *byte, unsigned char value)
{
    *byte = value;
}

void Mm_SetBytesNVM(unsigned short *bytes, unsigned short value)
{
    Mm_SetByteNVM((unsigned char *) bytes,(unsigned char) (value >> 8));
    Mm_SetByteNVM((unsigned char *) (bytes + 1),(unsigned char) (value));
}
