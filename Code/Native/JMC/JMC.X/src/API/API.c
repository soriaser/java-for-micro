#include "Common.h"
#include "API.h"
#include "APIMicroApplication.h"
#include "APIPortRegistry.h"
#include "Stack.h"

#define API_ID_MICROAPPLICATION_INIT            0x00
#define API_ID_MICROAPPLICATION_MAIN            0x01
#define API_ID_MICROAPPLICATION_SLEEP           0x02
#define API_ID_PORTREGISTRY_GETPORTREGISTRY     0x03
#define API_ID_PORTREGISTRY_SETEVENT            0x04
#define API_ID_PORTREGISTRY_SETPINTOZERO        0x06
#define API_ID_PORTREGISTRY_SETPINTOONE         0x07
#define API_ID_PORTREGISTRY_SETINPUTPIN         0x09
#define API_ID_PORTREGISTRY_SETOUTPUTPIN        0x0A

void Api_ExecuteNativeMethod(uint8_t id)
{
    uint16_t value = Stack_Pop();

    switch (id) {
        case API_ID_MICROAPPLICATION_INIT:
        case API_ID_MICROAPPLICATION_MAIN:
            break;
        case API_ID_MICROAPPLICATION_SLEEP:
            API_MicroApplication_Sleep(value);
            break;
        case API_ID_PORTREGISTRY_GETPORTREGISTRY:
            Api_PortRegistry_GetPortRegistry(value);
            break;
        case API_ID_PORTREGISTRY_SETEVENT:
            Api_PortRegistry_SetEvent(value);
            break;
        case API_ID_PORTREGISTRY_SETPINTOZERO:
            Api_PortRegistry_SetPinToZero((uint8_t) value);
            break;
        case API_ID_PORTREGISTRY_SETPINTOONE:
            Api_PortRegistry_SetPinToOne((uint8_t) value);
            break;
        case API_ID_PORTREGISTRY_SETINPUTPIN:
            Api_PortRegistry_SetInputPin((uint8_t) value);
            break;
        case API_ID_PORTREGISTRY_SETOUTPUTPIN:
            Api_PortRegistry_SetOutputPin((uint8_t) value);
            break;
    }

    Stack_Push(value);
}
