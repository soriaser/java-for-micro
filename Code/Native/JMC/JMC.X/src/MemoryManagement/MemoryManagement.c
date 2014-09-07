#include "Common.h"
#include "MemoryManagement.h"
#include "MemoryManagement_PIC18F4520.h"

void Mm_SetU08(uint32_t *pointer, uint8_t value)
{
    Mm_WriteNVM((uint32_t) pointer, 1, (uint8_t *) &value);
}