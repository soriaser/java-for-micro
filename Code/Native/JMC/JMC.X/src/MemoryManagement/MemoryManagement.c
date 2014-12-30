#include "Common.h"
#include "MemoryManagement.h"
#include "MemoryManagement_PIC18F4520.h"

uint8_t Mm_GetU08(uint32_t address)
{
    uint8_t value = 0x00;
    Mm_ReadNVM((uint32_t) address, 1, (uint8_t *) &value);
    return value;
}

uint16_t Mm_GetU16(uint32_t address)
{
    uint16_t value = 0x00;
    Mm_ReadNVM((uint32_t) address, 2, (uint8_t *) &value);
    return value;
}

void Mm_SetU08(uint32_t address, uint8_t value)
{
    Mm_WriteNVM((uint32_t) address, 1, (uint8_t *) &value);
}

void Mm_SetU16(uint32_t address, uint16_t value)
{
    Mm_WriteNVM((uint32_t) address, 2, (uint8_t *) &value);
}
