#include "Common.h"
#include "MemoryManagement_PIC18F4520.h"

#define MEMORY_SIZE_EEPROM          (uint32_t) 0x000000FF
#define MEMORY_SIZE_FLASH           (uint32_t) 0x000077FF

#define MEMORY_ADDRESS_EEPROM_START (uint32_t) 0x00000000
#define MEMORY_ADDRESS_EEPROM_END \
    (uint32_t) (MEMORY_ADDRESS_EEPROM_START + MEMORY_SIZE_EEPROM)
#define MEMORY_ADDRESS_FLASH_START  (uint32_t) 0x00000800
#define MEMORY_ADDRESS_FLASH_END \
    (uint32_t) (MEMORY_ADDRESS_FLASH_START + MEMORY_SIZE_FLASH)

#define MEMORY_SIZE_WRITE_BLOCK_FLASH 32

uint8_t Mm_IsAddressEEPROM(uint32_t address)
{
    if ((MEMORY_ADDRESS_EEPROM_START <= address) &&
            (MEMORY_ADDRESS_EEPROM_END >= address)) {
        return 0x01;
    }

    return 0x00;
}

uint8_t Mm_IsAddressFlash(uint32_t address)
{
    if ((MEMORY_ADDRESS_FLASH_START <= address) &&
            (MEMORY_ADDRESS_FLASH_END >= address)) {
        return 0x01;
    }

    return 0x00;
}

void Mm_Write(void)
{
    uint8_t GIEBit = INTCONbits.GIE;

    EECON1bits.CFGS = 0;  // EEPROM or Flash Access
    EECON1bits.WREN = 1;  // Allow write cycles

    INTCONbits.GIE = 0;

    EECON2 = 0x55;
    EECON2 = 0xAA;

    EECON1bits.WR = 1; // Start write
    while (EECON1bits.WR) {} // Wait until write complete

    INTCONbits.GIE = GIEBit;
    EECON1bits.WREN = 0;
}

void Mm_WriteEEPROM(uint32_t address, uint32_t bytes, uint8_t *data)
{
    for (uint32_t byte = 0; byte < bytes; byte++) {
        EEADR = (address & MEMORY_SIZE_EEPROM);
        EEDATA = *data++;
        EECON1bits.EEPGD = 0;
        Mm_Write();
        address++;
    }
}

void Mm_WriteFlash(uint32_t address, uint32_t bytes, uint8_t *data)
{
    uint8_t block;
    uint32_t saddress = address;

    address /= MEMORY_SIZE_WRITE_BLOCK_FLASH;
    address *= MEMORY_SIZE_WRITE_BLOCK_FLASH;
    address += MEMORY_SIZE_WRITE_BLOCK_FLASH;

    block = address - saddress;

    while(bytes) {
        TBLPTR = saddress & MEMORY_SIZE_FLASH;

        while(block--) {
            TABLAT = *data++;
            asm("TBLWTPOSTINC");

            if(0 == (--bytes)) {
                break;
            }
        }

        // Erase
        EECON1bits.FREE = 1;
        TBLPTR = saddress & MEMORY_SIZE_FLASH;
        Mm_Write();

        // Write
        EECON1bits.FREE = 0;  // Allow write
        TBLPTR = saddress & MEMORY_SIZE_FLASH;
        EECON1bits.EEPGD = 1; // Flash Access
        Mm_Write();

        // Increment to one block of 64 bytes
        block = MEMORY_SIZE_WRITE_BLOCK_FLASH;
        saddress += MEMORY_SIZE_WRITE_BLOCK_FLASH;
    }
}

void Mm_WriteNVM(uint32_t address, uint32_t bytes, uint8_t *data)
{
    if (Mm_IsAddressEEPROM(address)) {
        Mm_WriteEEPROM(address, bytes, data);
    } else if (Mm_IsAddressFlash(address)) {
        Mm_WriteFlash(address, bytes, data);
    } else {
        // TODO: Endless loop
    }
}

void Mm_ReadEEPROM(uint32_t address, uint32_t bytes, uint8_t *data)
{
    while(bytes--)
    {
        EEADR = (address & MEMORY_SIZE_EEPROM);
        EECON1bits.EEPGD = 0; // EEPROM Access
        EECON1bits.CFGS = 0;  // EEPROM or Flash Access
        EECON1bits.RD = 1;    // Start Read

        NOP();
        NOP();

        *data++ = EEDATA;
        address++;
    }
}

void Mm_ReadFlash(uint32_t address, uint32_t bytes, uint8_t *data)
{
    TBLPTR = address & MEMORY_SIZE_FLASH;

    while(bytes--)
    {
        asm("TBLRDPOSTINC");
        *data++ = TABLAT;
    }

    // restore the TABLE pointer
    TBLPTR = address & MEMORY_SIZE_FLASH;
}

void Mm_ReadNVM(uint32_t address, uint32_t bytes, uint8_t *data)
{
    if (Mm_IsAddressEEPROM(address)) {
        Mm_ReadEEPROM(address, bytes, data);
    } else if (Mm_IsAddressFlash(address)) {
        Mm_ReadFlash(address, bytes, data);
    } else {
        // TODO: Endless loop
    }
}
