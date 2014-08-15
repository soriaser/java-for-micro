#include "MemoryManagement.h"

unsigned char Mm_GetByteNVM(unsigned char *byte)
{
    return *byte;
}

void Mm_SetByteNVM(unsigned char *byte, unsigned char value)
{
    *byte = value;
}
