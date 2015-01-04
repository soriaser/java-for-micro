#include "Common.h"

#include "Timer.h"
#include "Loader.h"
#include "SerialPort.h"

void Timer_T0_Init(uint8_t interruption)
{
    if (interruption) {
        INTCON = 0xC0;
        TMR0IE = 1;
    }

    T0CON = 0x48;
}

void Timer_T0_ISR(void)
{
    if (LOADER_ENABLED == Loader_IsLoaderEnabled) {
        // Stop Timer 0
        Timer_T0_Stop();
        // Send wait byte
        SerialPort_Send(LOADER_ACK_WAIT);
        // Restart Timer 0
        Timer_T0_Start();
    }

    TMR0IF = 0;
}
