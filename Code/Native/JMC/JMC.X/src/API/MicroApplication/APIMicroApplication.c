#include "Common.h"
#include "API.h"
#include "APIMicroApplication.h"
#include "APIPortRegistry.h"
#include "APISerialPort.h"

void Api_MicroApplication_ClearEvent(uint8_t event)
{
    switch (event) {
        case API_PORTREGISTRY_EVENT_INT0:
            Port_ClearEvent(API_PORTREGISTRY_EVENT_INT0);
            Api_EventsRegistered.int0 = 0;
            break;
        case API_SERIALPORT_EVENT_RECEIVED_BYTE:
            Api_EventsRegistered.receive = 0;
            break;
    }
}

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

void API_MicroApplication_Sleep(uint16_t value)
{
    for (uint16_t loop = 0; loop < value; loop++) {
        __delay_ms(1);
    }
}
