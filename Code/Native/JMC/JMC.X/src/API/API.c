#include "Common.h"
#include "API.h"
#include "APIMicroApplication.h"
#include "APIPortRegistry.h"
#include "APISerialPort.h"
#include "Heap.h"
#include "Stack.h"

#define API_ID_MICROAPPLICATION_INIT            0x00
#define API_ID_MICROAPPLICATION_SLEEP           0x01
#define API_ID_PORTREGISTRY_GETPORT             0x02
#define API_ID_PORTREGISTRY_SETEVENT            0x03
#define API_ID_PORTREGISTRY_SETPINTOZERO        0x05
#define API_ID_PORTREGISTRY_SETPINTOONE         0x06
#define API_ID_PORTREGISTRY_SETINPUTPIN         0x08
#define API_ID_PORTREGISTRY_SETOUTPUTPIN        0x09
#define API_ID_SERIALPORT_GETSERIALPORT         0x0A
#define API_ID_SERIALPORT_ENABLE                0x0B
#define API_ID_SERIALPORT_DISABLE               0x0C
#define API_ID_SERIALPORT_SEND                  0x0D

api_events_t Api_Events;

void Api_Execute_SerialPort_Send()
{
    uint16_t size = Stack_Pop();
    uint16_t offset = Stack_Pop();
    uint8_t *buffer = (uint8_t *) Heap_GetHeaderAddress(Stack_Pop())
            + 1;
    API_SerialPort_Send(buffer, offset, size);
}

void Api_ExecuteNativeMethod(uint8_t id)
{
    switch (id) {
        case API_ID_MICROAPPLICATION_INIT:
            Stack_Pop();
            break;
        case API_ID_MICROAPPLICATION_SLEEP:
            API_MicroApplication_Sleep(Stack_Pop());
            Stack_Pop();
            break;
        case API_ID_PORTREGISTRY_GETPORT:
            Api_PortRegistry_GetPortRegistry(Stack_Pop());
            Stack_Push(0);
            break;
        case API_ID_PORTREGISTRY_SETEVENT:
            Api_PortRegistry_SetEvent(Stack_Pop());
            Stack_Pop();
            break;
        case API_ID_PORTREGISTRY_SETPINTOZERO:
            Api_PortRegistry_SetPinToZero(Stack_Pop());
            Stack_Pop();
            break;
        case API_ID_PORTREGISTRY_SETPINTOONE:
            Api_PortRegistry_SetPinToOne(Stack_Pop());
            Stack_Pop();
            break;
        case API_ID_PORTREGISTRY_SETINPUTPIN:
            Api_PortRegistry_SetInputPin(Stack_Pop());
            Stack_Pop();
            break;
        case API_ID_PORTREGISTRY_SETOUTPUTPIN:
            Api_PortRegistry_SetOutputPin(Stack_Pop());
            Stack_Pop();
            break;
        case API_ID_SERIALPORT_ENABLE:
            Api_SerialPort_SetEvent(0x01);
            Stack_Pop();
            break;
        case API_ID_SERIALPORT_DISABLE:
            Api_SerialPort_SetEvent(0x00);
            Stack_Pop();
            break;
        case API_ID_SERIALPORT_GETSERIALPORT:
            Stack_Push(0);
            break;
        case API_ID_SERIALPORT_SEND:
            Api_Execute_SerialPort_Send();
            Stack_Pop();
            break;
    }
}
