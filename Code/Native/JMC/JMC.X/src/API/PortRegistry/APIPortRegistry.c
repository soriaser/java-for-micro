#include "Common.h"
#include "APIPortRegistry.h"

uint8_t *Api_PortRegistry_Port = NULL;

uint8_t *Api_PortRegistry_Tris = NULL;

uint8_t Api_PortRegistry_Events = 0x00;

void Api_PortRegistry_GetPortRegistry(uint8_t port)
{
    switch (port) {
        case API_PORTREGISTRY_PORTA:
            Api_PortRegistry_Port = (uint8_t *) &PORTA;
            Api_PortRegistry_Tris = (uint8_t *) &TRISA;
            break;
        case API_PORTREGISTRY_PORTB:
            Api_PortRegistry_Port = (uint8_t *) &PORTB;
            Api_PortRegistry_Tris = (uint8_t *) &TRISB;
            break;
        case API_PORTREGISTRY_PORTC:
            Api_PortRegistry_Port = (uint8_t *) &PORTC;
            Api_PortRegistry_Tris = (uint8_t *) &TRISC;
            break;
    }
}

void Api_PortRegistry_SetEvent(uint8_t event)
{
    Api_PortRegistry_Events = event;

    if (API_PORTREGISTRY_EVENT_INT0 & Api_PortRegistry_Events) {
        INTCON  |= 0x10;
        INTCON2 |= 0x80;
        INTEDG0  = 1;
    }
}

void Api_PortRegistry_SetPin(uint8_t pins, uint8_t type)
{
    switch (type) {
        case API_PORTREGISTRY_SETZERO:
            pins = ~pins;
            (*Api_PortRegistry_Port) &= pins;
            break;
        case API_PORTREGISTRY_SETOUTPUT:
            pins = ~pins;
            (*Api_PortRegistry_Tris) &= pins;
            break;
        case API_PORTREGISTRY_SETONE:
            (*Api_PortRegistry_Port) |= pins;
            break;
        case API_PORTREGISTRY_SETINPUT:
            (*Api_PortRegistry_Tris) |= pins;
            break;
    }
}
