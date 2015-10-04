#include "Common.h"
#include "MemoryManagement_PIC18F4520.h"

#if (PLATFORM == PLATFORM_PIC18F4520)

#include "flash.h"

#define MEMORY_SIZE_EEPROM          (mm_address_t) 0x00FF
#define MEMORY_SIZE_FLASH           (mm_address_t) 0x77FF

#define MEMORY_ADDRESS_EEPROM_START (mm_address_t) 0x0000
#define MEMORY_ADDRESS_EEPROM_END \
    (uint32_t) (MEMORY_ADDRESS_EEPROM_START + MEMORY_SIZE_EEPROM)
#define MEMORY_ADDRESS_FLASH_START  (mm_address_t) 0x0800
#define MEMORY_ADDRESS_FLASH_END \
    (uint32_t) (MEMORY_ADDRESS_FLASH_START + MEMORY_SIZE_FLASH)

#define MEMORY_SIZE_WRITE_BLOCK_FLASH 64

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
        EECON1bits.CFGS = 0;  // EEPROM or Flash Access
        EECON1bits.RD = 1;    // Start Read

        NOP();
        NOP();

        *data++ = EEDATA;
        address++;
    }
}

void Mm_ReadFlash(mm_address_t address, mm_address_t bytes, uint8_t *data)
{
    ReadFlash(address, bytes, data);
    /*
    uint8_t offset = 0x00;

    TBLPTR = address;

    while(bytes--)
    {
        //asm("TBLRDPOSTINC");
        data[offset] = TABLAT;
        offset++;
        //asm("MOVF TABLAT, W");
        asm("TBLRD*+");
    }
    asm("TBLRD*-");

    // restore the TABLE pointer
    TBLPTR = address;
    */
}

void Mm_ReadNVM(mm_address_t address, mm_address_t bytes, uint8_t *data)
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

void Mm_WriteEEPROM(mm_address_t address, mm_address_t bytes, uint8_t *data)
{
    for (mm_address_t byte = 0; byte < bytes; byte++) {
        EEADR = (address & MEMORY_SIZE_EEPROM);
        EEDATA = *data++;
        EECON1bits.EEPGD = 0;
        Mm_Write();
        address++;
    }
}

/*
void Mm_WriteFlashBlock(mm_address_t address, uint8_t *block)
{
    TBLPTR = address;

    for (uint8_t offset = 0x00; offset < MEMORY_SIZE_WRITE_BLOCK_FLASH;
            offset++) {
        TABLAT = block[offset];
        asm("TBLWTPOSTINC");
        //asm("TBLWT*+");
    }
    //asm("TBLRD*-");

    // Write block
    EECON1bits.FREE = 0;
    TBLPTR = address;
    EECON1bits.EEPGD = 1; // Flash Access
    Mm_Write();
}
*/

void Mm_WriteFlash(mm_address_t address, mm_address_t bytes, uint8_t *data)
{
/*
    EraseFlash((unsigned long) address, (unsigned long) (address + bytes));
    WriteBytesFlash((unsigned long) address, (unsigned int) bytes, data);
*/

    uint8_t block[MEMORY_SIZE_WRITE_BLOCK_FLASH];
    mm_address_t saddress = address;

    address /= MEMORY_SIZE_WRITE_BLOCK_FLASH;
    address *= MEMORY_SIZE_WRITE_BLOCK_FLASH;

    while (bytes) {
        uint8_t dataOffset = 0x00;

        //Mm_ReadFlash(address, MEMORY_SIZE_WRITE_BLOCK_FLASH, block);
        ReadFlash(address, MEMORY_SIZE_WRITE_BLOCK_FLASH, block);

        for (uint8_t offset = saddress - address;
                (offset < MEMORY_SIZE_WRITE_BLOCK_FLASH) && (bytes > 0);
                offset++) {
            block[offset] = data[dataOffset];
            bytes--;
            dataOffset++;
        }

        // Erase block
        //EECON1bits.FREE = 1; // Allow erase
        //TBLPTR = address;
        //EECON1bits.EEPGD = 1; // Flash Access
        //Mm_Write();
        EraseFlash(address, address + MEMORY_SIZE_WRITE_BLOCK_FLASH);

        // Write block
        //Mm_WriteFlashBlock(address, block);
        WriteBytesFlash(address, MEMORY_SIZE_WRITE_BLOCK_FLASH, block);

        address += MEMORY_SIZE_WRITE_BLOCK_FLASH;
        saddress = address;
    }
}

void Mm_WriteNVM(mm_address_t address, mm_address_t bytes, uint8_t *data)
{
    if (Mm_IsAddressEEPROM(address)) {
        Mm_WriteEEPROM(address, bytes, data);
    } else if (Mm_IsAddressFlash(address)) {
        Mm_WriteFlash(address, bytes, data);
    } else {
        // TODO: Endless loop
    }
}

#endif // (PLATFORM == PLATFORM_PIC18F4520)
