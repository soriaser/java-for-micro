#include "Common.h"
#include "API.h"
#include "APIMicroApplication.h"
#include "APIPortRegistry.h"
#include "APISerialPort.h"
#include "APITimer.h"
#include "Heap.h"
#include "JVM.h"
#include "Stack.h"

#define API_ID_MICROAPPLICATION_INIT            0x00
#define API_ID_MICROAPPLICATION_CLEAREVENT      0x01
#define API_ID_MICROAPPLICATION_SETEVENT        0x02
#define API_ID_MICROAPPLICATION_SLEEP           0x03
#define API_ID_PORTREGISTRY_GETPORT             0x04
#define API_ID_PORTREGISTRY_SETPINTOZERO        0x05
#define API_ID_PORTREGISTRY_SETPINTOONE         0x06
#define API_ID_PORTREGISTRY_SETINPUTPIN         0x07
#define API_ID_PORTREGISTRY_SETOUTPUTPIN        0x08
#define API_ID_PORTREGISTRY_SETIO               0x09
#define API_ID_PORTREGISTRY_SETPINS             0x0A
#define API_ID_SERIALPORT_RECEIVE               0x0B
#define API_ID_SERIALPORT_SEND                  0x0C
#define API_ID_TIMER_CLEAR                      0x0D
#define API_ID_TIMER_DISABLE                    0x0E
#define API_ID_TIMER_ENABLE                     0x0F
#define API_ID_TIMER_GETTIMER                   0x10
#define API_ID_TIMER_READ                       0x11

api_events_t Api_Events;

api_events_t Api_EventsRegistered;

void Api_Execute_SerialPort_Send()
{
    uint16_t size = Stack_Pop();
    uint16_t offset = Stack_Pop();
    uint8_t *buffer = (uint8_t *) Heap_GetHeaderAddress(Stack_Pop())
            + sizeof(heap_t) + 1;
    API_SerialPort_Send(buffer, offset, size);
}

void Api_ExecuteNativeMethod(uint8_t id, uint8_t isStatic)
{
    uint16_t aux = 0;
    uint8_t addToStack = 0x00;

    switch (id) {
        case API_ID_MICROAPPLICATION_INIT:
            break;
        case API_ID_MICROAPPLICATION_CLEAREVENT:
            Api_MicroApplication_ClearEvent(Stack_Pop());
            break;
        case API_ID_MICROAPPLICATION_SETEVENT:
            Api_MicroApplication_SetEvent(Stack_Pop());
            break;
        case API_ID_MICROAPPLICATION_SLEEP:
            API_MicroApplication_Sleep(Stack_Pop());
            break;
        case API_ID_PORTREGISTRY_GETPORT:
            Api_PortRegistry_GetPortRegistry(Stack_Pop());
            aux = 0x0080;
            addToStack++;
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
        case API_ID_PORTREGISTRY_SETIO:
            Api_PortRegistry_SetIO(Stack_Pop());
            break;
        case API_ID_PORTREGISTRY_SETPINS:
            Api_PortRegistry_SetPins(Stack_Pop());
            break;
        case API_ID_SERIALPORT_RECEIVE:
            aux = (uint16_t) (API_SerialPort_Receive() & 0x00FF);
            addToStack++;
            break;
        case API_ID_SERIALPORT_SEND:
            Api_Execute_SerialPort_Send();
            break;
        case API_ID_TIMER_CLEAR:
            Api_Timer_Clear();
            break;
        case API_ID_TIMER_DISABLE:
            Api_Timer_Disable();
            break;
        case API_ID_TIMER_ENABLE:
            Api_Timer_Enable();
            break;
        case API_ID_TIMER_GETTIMER:
            Api_Timer_GetTimer(Stack_Pop());
            aux = 0x0081;
            addToStack++;
            break;
        case API_ID_TIMER_READ:
            aux = Api_Timer_Read();
            addToStack++;
            break;
    }

    if (isStatic == 0x00) {
        // Get "this"
        Stack_Pop();
    }

    if (addToStack > 0x00) {
        Stack_Push(aux);
    }
}
