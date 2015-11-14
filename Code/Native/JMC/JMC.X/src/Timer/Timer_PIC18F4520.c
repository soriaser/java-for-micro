#include "Common.h"
#include "APITimer.h"
#include "Timer_PIC18F4520.h"

#if (PLATFORM == PLATFORM_PIC18F4520)

void Timer_Clear()
{
    switch (Api_Timer_CurrentTimer) {
        case API_TIMER_TIMER_0:
            break;
        case API_TIMER_TIMER_1:
#ifdef STORE_TIMER_IF_INT0
            //Timer_ValueRead = 0;
#endif // STORE_TIMER_IF_INT0
            WRITETIMER1(0x0000);
            break;
    }
}

void Timer_Disable()
{
    switch (Api_Timer_CurrentTimer) {
        case API_TIMER_TIMER_0:
            break;
        case API_TIMER_TIMER_1:
            TMR1ON = 0;
            break;
    }
}

void Timer_Enable()
{
    switch (Api_Timer_CurrentTimer) {
        case API_TIMER_TIMER_0:
            break;
        case API_TIMER_TIMER_1:
            T1CON = 0xB8;
            WRITETIMER1(0x0000);
#ifdef STORE_TIMER_IF_INT0
            //Timer_ValueRead = 0;
#endif // STORE_TIMER_IF_INT0
            TMR1IE = 0;
            TMR1ON = 1;
            break;
    }
}

void Timer_GetTimer(uint8_t timer)
{
    Api_Timer_CurrentTimer = timer;
}

uint16_t Timer_Read()
{
    switch (Api_Timer_CurrentTimer) {
        case API_TIMER_TIMER_0:
            break;
        case API_TIMER_TIMER_1:
#ifdef STORE_TIMER_IF_INT0
            //return Timer_ValueRead;
            return (uint16_t) READTIMER1();
#else
            return (uint16_t) READTIMER1();
#endif // STORE_TIMER_IF_INT0
    }

    return (uint16_t) -1;
}

#endif // (PLATFORM == PLATFORM_PIC18F4520)