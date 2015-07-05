#include "Common.h"
#include "MemoryManagement.h"

void Mm_CopyRamHigherAddress(uint8_t *destination, uint8_t *source,
        uint16_t size)
{
    destination += size;
    source += size;

    while (size > 0) {
        *(destination) = *(source);

        destination--;
        source--;

        size--;
    }

    *(destination) = *(source);
}

void Mm_CopyRamLowerAddress(uint8_t *destination, uint8_t *source,
        uint16_t size)
{
    while (size > 0) {
        *(destination) = *(source);

        destination++;
        source++;

        size--;
    }
}

void Mm_CopyRam(uint8_t *destination, uint8_t *source, uint16_t size)
{
    if (destination > source) {
        Mm_CopyRamHigherAddress(destination, source, size);
    } else {
        Mm_CopyRamLowerAddress(destination, source, size);
    }
}

uint8_t Mm_GetU08(mm_address_t address)
{
    uint8_t value = 0x00;
    Mm_ReadNVM(address, 1, (uint8_t *) &value);
    return value;
}

uint16_t Mm_GetU16(mm_address_t address)
{
    uint16_t value = 0x00;
    Mm_ReadNVM(address, 2, (uint8_t *) &value);
    return value;
}

void Mm_SetU08(mm_address_t address, uint8_t value)
{
    Mm_WriteNVM(address, 1, (uint8_t *) &value);
}

void Mm_SetU16(mm_address_t address, uint16_t value)
{
    Mm_WriteNVM(address, 2, (uint8_t *) &value);
}
