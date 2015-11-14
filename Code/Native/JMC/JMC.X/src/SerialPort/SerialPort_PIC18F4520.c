#include "Common.h"
#include "Loader.h"
#include "SerialPort_PIC18F4520.h"

#if (PLATFORM == PLATFORM_PIC18F4520)

#ifdef USE_STDIO_FOR_SERIAL_PORT
#include <stdio.h>
#endif // USE_STDIO_FOR_SERIAL_PORT

uint8_t SerialPort_CurrentValueRx = 0xFF;

void SerialPort_Init(void)
{
    INTCON = 0xC0;
    TRISC = 0xC0;
    BRG16 = 0;
    BRGH = 0;
    //SPBRG = ((_XTAL_FREQ / 16) / BAUDRATE) - 1;
    //SPBRG = ((_XTAL_FREQ / BAUDRATE) / 16) - 1;
    SPBRG = 25;
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

    // Store value
    SerialPort_CurrentValueRx = SerialPort_Receive();

    if (LOADER_ENABLED == Loader_IsLoaderEnabled) {
        // Disable Serial Port Interrupt
        SerialPort_DisableRx();
        // Mark as pending
        Loader_State = LOADER_STATE_PENDING;
    }
}

void SerialPort_Send(uint8_t byte)
{
#ifdef USE_STDIO_FOR_SERIAL_PORT
    printf("%d", byte);
#else
    while (!TXIF);
    TXREG = byte;
#endif // USE_STDIO_FOR_SERIAL_PORT
}

#endif // (PLATFORM == PLATFORM_PIC18F4520)
