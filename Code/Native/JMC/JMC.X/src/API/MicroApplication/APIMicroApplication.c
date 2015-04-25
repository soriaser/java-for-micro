#include "Common.h"
#include "API.h"
#include "APIMicroApplication.h"
#include "APIPortRegistry.h"
#include "APISerialPort.h"

void Api_MicroApplication_SetEvent(uint8_t event)
{
    switch (event) {
        case API_PORTREGISTRY_EVENT_INT0:
            Port_SetEvent(API_PORTREGISTRY_EVENT_INT0);
            Api_EventsRegistered.int0 = 1;
            break;
        case API_SERIALPORT_EVENT_RECEIVED_BYTE:
            Api_EventsRegistered.receive = 1;
            break;
    }
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
