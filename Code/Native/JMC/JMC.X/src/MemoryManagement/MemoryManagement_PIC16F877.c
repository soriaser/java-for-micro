#include "Common.h"
#include "MemoryManagement_PIC16F877.h"

#if (PLATFORM == PLATFORM_PIC16F877)

//#define MEMORY_SIZE_EEPROM          (mm_address_t) 0x00FF
#define MEMORY_SIZE_FLASH           (mm_address_t) 0x3FFF

//#define MEMORY_ADDRESS_EEPROM_START (mm_address_t) 0x0000
//#define MEMORY_ADDRESS_EEPROM_END \
//    (uint32_t) (MEMORY_ADDRESS_EEPROM_START + MEMORY_SIZE_EEPROM)
#define MEMORY_ADDRESS_FLASH_START  (mm_address_t) 0x0000
#define MEMORY_ADDRESS_FLASH_END \
    (uint32_t) (MEMORY_ADDRESS_FLASH_START + MEMORY_SIZE_FLASH)

//#define MEMORY_SIZE_WRITE_BLOCK_FLASH 64

/*
uint8_t Mm_IsAddressEEPROM(mm_address_t address)
{
    if (MEMORY_ADDRESS_EEPROM_END >= address) {
        return 0x01;
    }

    return 0x00;
}

uint8_t Mm_IsAddressFlash(mm_address_t address)
{
    if ((MEMORY_ADDRESS_FLASH_START <= address) &&
            (MEMORY_ADDRESS_FLASH_END >= address)) {
        return 0x01;
    }

    return 0x00;
}

void Mm_ReadEEPROM(mm_address_t address, mm_address_t bytes, uint8_t *data)
{
    while(bytes--)
    {
        EEADR = (address & MEMORY_SIZE_EEPROM);
        EECON1bits.EEPGD = 0; // EEPROM Access
        EECON1bits.RD = 1;    // Start Read

        (*data) = EEDATA;
        data++;
        address++;
    }
}

void Mm_ReadFlash(mm_address_t address, mm_address_t bytes, uint8_t *data)
{
    while(bytes--)
    {
        EEADRH = ((address & MEMORY_SIZE_FLASH) >> 8) & 0xFF;
        EEADR = (address & MEMORY_SIZE_FLASH);
        EECON1bits.EEPGD = 1; // Flash Access
        EECON1bits.RD = 1;    // Start Read

        NOP();
        NOP();

        *data++ = EEDATA;
        address++;
    }
}
*/

void Mm_ReadNVM(mm_address_t address, mm_address_t bytes, uint8_t *data)
{
/*
    if (Mm_IsAddressEEPROM(address)) {
        Mm_ReadEEPROM(address, bytes, data);
    } else if (Mm_IsAddressFlash(address)) {
        Mm_ReadFlash(address, bytes, data);
    } else {
        // TODO: Endless loop
    }
 */
    address &= MEMORY_SIZE_FLASH;

    while(bytes--)
    {
        EEADR   = (address)      & 0xFF;
        EEADRH  = (address >> 8) & 0xFF;
        EEPGD   = 1;
        RD      = 1;

        NOP();
        NOP();

        *data++ = EEDATA;
        address++;
    }
}

/*
void Mm_Write(void)
{
    CARRY = 0;

    if(GIE){
        CARRY = 1;
    }

    GIE = 0;
    WREN = 1;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    WR = 1;

    WREN = 0;

    if(CARRY) {
        GIE = 1;
    }
}

void Mm_WriteEEPROM(mm_address_t address, mm_address_t bytes, uint8_t *data)
{
    for (mm_address_t byte = 0; byte < bytes; byte++) {
        EEADR = (address & MEMORY_SIZE_EEPROM);
        EEDATA = *data++;
        EEPGD = 0;
        Mm_Write();
        address++;
    }
}

void Mm_WriteFlash(mm_address_t address, mm_address_t bytes, uint8_t *data)
{
    for (mm_address_t byte = 0; byte < bytes; byte++) {
        EEADR = (address & MEMORY_SIZE_FLASH);
        EEADRH = ((address & MEMORY_SIZE_FLASH) >> 8) & 0xFF;
        EEDATA = *data++;
        EEDATH = 0x00;
        EEPGD = 1;
        Mm_Write();
        address++;
    }
}
*/

void Mm_WriteNVM(mm_address_t address, mm_address_t bytes, uint8_t *data)
{
    /*
    if (Mm_IsAddressEEPROM(address)) {
        Mm_WriteEEPROM(address, bytes, data);
    } else if (Mm_IsAddressFlash(address)) {
        Mm_WriteFlash(address, bytes, data);
    } else {
        // TODO: Endless loop
    }
    */
    address &= MEMORY_SIZE_FLASH;

    CARRY = 0;
    if (GIE) {
        CARRY = 1;
    }
    GIE = 0;

    for (mm_address_t byte = 0; byte < bytes; byte++) {
        EEADR   = (address)      & 0xFF;
        EEADRH  = (address >> 8) & 0xFF;
        EEDATA  = (*data);
        EEDATH  = 0x00;
        EEPGD   = 1;
        WREN    = 1;
        EECON2  = 0x55;
        EECON2  = 0xAA;
        WR      = 1;

        NOP();
        NOP();

        WREN    = 0;
        data++;
        address++;
    }

    if (CARRY) {
        GIE = 1;
    }
}

#endif //(PLATFORM == PLATFORM_PIC16F877)
