#include "Common.h"

#include "Timer.h"
#include "Loader.h"
#include "SerialPort.h"

void Timer_T0_ISR(void)
{
    if (LOADER_ENABLED == Loader_IsLoaderEnabled) {
        // Stop Timer 0
        Timer_T0_Stop();
        // Send wait byte
        SerialPort_Send(LOADER_WAIT_BYTE);
        // Restart Timer 0
        Timer_T0_Start();
    }

    TMR0IF = 0;
}
