#include "Common.h"
#include "APIMicroApplication.h"
#include "APIPortRegistry.h"

uint8_t Api_MicroApplication_Events = 0x00;

void Api_MicroApplication_SetEvent(uint8_t event)
{
    if (API_PORTREGISTRY_EVENT_INT0 & event) {
        Port_SetEvent(API_PORTREGISTRY_EVENT_INT0);
    }

    Api_MicroApplication_Events |= event;
}

/*
void API_MicroApplication_Sleep(uint16_t value)
{
    uint32_t counter = ((value * 1000) / TIMER0_OVERFLOW_USEC);

    Timer_T0_Init(0x00);

    while (0x01) {
        Timer_T0_Start();

        while (!TMR0IF) {}
        TMR0IF = 0;
        counter--;

        if (0x00 >= counter) {
            Timer_T0_Stop();
            Timer_T0_Reset();
            return;
        }
    }
}
*/
