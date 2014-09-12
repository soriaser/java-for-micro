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

#define MEMORY_SIZE_WRITE_BLOCK_FLASH 64

uint8_t Mm_IsAddressEEPROM(uint32_t address)
{
    if (MEMORY_ADDRESS_EEPROM_END >= address) {
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
    TBLPTR = address;

    while(bytes--)
    {
        asm("TBLRDPOSTINC");
        *data++ = TABLAT;
    }

    // restore the TABLE pointer
    TBLPTR = address;
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

void Mm_WriteFlashBlock(uint32_t address, uint8_t *block)
{
    TBLPTR = address;

    for (uint8_t offset = 0x00; offset < MEMORY_SIZE_WRITE_BLOCK_FLASH;
            offset++) {
        TABLAT = *block++;
        asm("TBLWTPOSTINC");
    }

    // Write block
    EECON1bits.FREE = 0;
    TBLPTR = address;
    EECON1bits.EEPGD = 1; // Flash Access
    Mm_Write();
}

void Mm_WriteFlash(uint32_t address, uint32_t bytes, uint8_t *data)
{
    uint8_t block[MEMORY_SIZE_WRITE_BLOCK_FLASH];
    uint32_t saddress = address;

    address /= MEMORY_SIZE_WRITE_BLOCK_FLASH;
    address *= MEMORY_SIZE_WRITE_BLOCK_FLASH;

    while (bytes) {

        Mm_ReadFlash(address, MEMORY_SIZE_WRITE_BLOCK_FLASH, block);

        for (uint8_t offset = saddress - address;
                (offset < MEMORY_SIZE_WRITE_BLOCK_FLASH) && (bytes > 0);
                offset++) {
            block[offset] = *data++;
            bytes--;
        }

        // Erase block
        EECON1bits.FREE = 1; // Allow erase
        TBLPTR = address;
        EECON1bits.EEPGD = 1; // Flash Access
        Mm_Write();

        // Write block
        Mm_WriteFlashBlock(address, block);

        address += MEMORY_SIZE_WRITE_BLOCK_FLASH;
        saddress = address;
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
