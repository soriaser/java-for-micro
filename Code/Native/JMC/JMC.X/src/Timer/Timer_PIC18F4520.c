#include "Common.h"
#include "APITimer.h"
#include "Timer_PIC18F4520.h"

void Timer_Clear()
{
    switch (Api_Timer_CurrentTimer) {
        case API_TIMER_TIMER_0:
            break;
        case API_TIMER_TIMER_1:
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
            TMR1IE = 0;
            T1CON = 0x88;
            TMR1ON = 0;
            TMR1L = 0x00;
            TMR1H = 0x00;
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
            return (uint16_t) READTIMER1();
    }

    return (uint16_t) -1;
}