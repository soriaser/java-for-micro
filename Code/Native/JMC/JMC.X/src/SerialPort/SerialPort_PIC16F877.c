#include "Common.h"
#include "Loader.h"
#include "SerialPort_PIC16F877.h"

#if (PLATFORM == PLATFORM_PIC16F877)

uint8_t SerialPort_CurrentValueRx = 0xFF;

void SerialPort_Init(void)
{
    TRISC6  = 1; // TX Pin
    TRISC7  = 1; // RX Pin
    //SPBRG   = ((_XTAL_FREQ / 64) / BAUDRATE) - 1;
    SPBRG   = 25;
    BRGH    = 0; // Fast baudrate
    SYNC    = 0; // Asynchronous
    SPEN    = 1; // Configures RC7 and RC6 pins as serial port pins
    CREN    = 1; // Enables continuous receive
    SREN    = 0; // No effect in asynchronous mode
    TXIE    = 0; // Disables the USART transmit interrupt
    RCIE    = 1; // Enables the USART receive interrupt
    TX9     = 0; // 8-bit transmission
    RX9     = 0; // 8-bit reception
    TXEN    = 0; // Reset transmitter
    TXEN    = 1; // Enable transmitter
    GIE     = 1; // Enable global interrupts
    PEIE    = 1; // Enable pripherical interrupts
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
    while (!TXIF);
    TXREG = byte;
}

#endif //(PLATFORM == PLATFORM_PIC16F877)
