#include "Common.h"
#include "API.h"
#include "APIMicroApplication.h"
#include "APIPortRegistry.h"
#include "Stack.h"

#define API_ID_MICROAPPLICATION_INIT            0x00
#define API_ID_MICROAPPLICATION_SLEEP           0x01
#define API_ID_PORTREGISTRY_GETPORTREGISTRY     0x02
#define API_ID_PORTREGISTRY_SETEVENT            0x03
#define API_ID_PORTREGISTRY_SETPINTOZERO        0x05
#define API_ID_PORTREGISTRY_SETPINTOONE         0x06
#define API_ID_PORTREGISTRY_SETINPUTPIN         0x08
#define API_ID_PORTREGISTRY_SETOUTPUTPIN        0x09

void Api_ExecuteNativeMethod(uint8_t id)
{
    switch (id) {
        case API_ID_MICROAPPLICATION_INIT:
            Stack_Pop();
            break;
        case API_ID_MICROAPPLICATION_SLEEP:
            API_MicroApplication_Sleep(Stack_Pop());
            break;
        case API_ID_PORTREGISTRY_GETPORTREGISTRY:
            Api_PortRegistry_GetPortRegistry(Stack_Pop());
            break;
        case API_ID_PORTREGISTRY_SETEVENT:
            Api_PortRegistry_SetEvent(Stack_Pop());
            break;
        case API_ID_PORTREGISTRY_SETPINTOZERO:
            Api_PortRegistry_SetPinToZero(Stack_Pop());
            break;
        case API_ID_PORTREGISTRY_SETPINTOONE:
            Api_PortRegistry_SetPinToOne(Stack_Pop());
            break;
        case API_ID_PORTREGISTRY_SETINPUTPIN:
            Api_PortRegistry_SetInputPin(Stack_Pop());
            break;
        case API_ID_PORTREGISTRY_SETOUTPUTPIN:
            Api_PortRegistry_SetOutputPin(Stack_Pop());
            break;
    }
}
