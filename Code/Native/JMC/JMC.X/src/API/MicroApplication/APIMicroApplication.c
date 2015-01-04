#include "Common.h"
#include "APIMicroApplication.h"
#include "Timer.h"

void API_MicroApplication_Sleep(uint16_t value)
{
    uint32_t counter = ((value * 1000) / TIMER0_OVERFLOW_USEC);

    Timer_T0_Init(0x00);

    while (0x01) {
        Timer_T0_Reset();
        Timer_T0_Start();

        while (!TMR0IF) {}
        TMR0IF = 0;
        counter--;

        if (0x00 >= counter) {
            Timer_T0_Stop();
            break;
        }
    }
}
