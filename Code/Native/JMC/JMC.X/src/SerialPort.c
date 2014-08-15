#include "Common.h"

#include "Loader.h"
#include "MemoryManagement.h"
#include "SerialPort.h"

#define SERIALPORT_RX_BUFFER_SIZE 10

void SerialPort_Init(void)
{
    INTCON = 0xC0;
    TRISC = 0xC0;
    BRG16 = 0;
    BRGH = 0;
    SPBRG = ((_XTAL_FREQ / 64) / BAUDRATE) - 1;
    TX9 = 0;
    SYNC = 0;
    RX9 = 0;
    SPEN = 1;
    SREN = 0;
    CREN = 1;
    RCIE = 1;
    TXIE = 0;
    TXEN = 1;
}

void SerialPort_ISR(void)
{
    if (OERR) {
        CREN = 0;
        CREN = 1;
    }

    if (LOADER_ENABLED == 
            Mm_GetByteNVM((unsigned char *) &Loader_IsLoaderEnabled)) {
        Loader_ISR();
    }

    RCIF = 0;
}

void SerialPort_Send(unsigned char byte)
{
    while (!TXIF);
    TXREG = byte;
}
