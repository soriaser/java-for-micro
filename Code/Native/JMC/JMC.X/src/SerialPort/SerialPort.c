#include "Common.h"

#include "JMC.h"
#include "Loader.h"
#include "Timer.h"
#include "MemoryManagement.h"
#include "SerialPort.h"

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

    if (LOADER_ENABLED == Loader_IsLoaderEnabled) {
        // Store value
        Loader_CurrentValue = RCREG;
        // Disable Serial Port Interrupt
        SerialPort_DisableRx();
        // Start Timer
        Timer_T0_Start();

        // Mark as pending
        Loader_LoaderState |= LOADER_STATE_PENDING;
    }

    RCIF = 0;
}

void SerialPort_Send(uint8_t byte)
{
    while (!TXIF);
    TXREG = byte;
}
