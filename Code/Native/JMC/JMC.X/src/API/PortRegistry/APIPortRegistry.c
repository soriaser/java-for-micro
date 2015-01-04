#include "Common.h"
#include "APIPortRegistry.h"

uint8_t *Api_PortRegistry_Port = NULL;

void Api_PortRegistry_GetPortRegistry(uint8_t port)
{
    switch (port) {
        case API_PORTREGISTRY_PORTA:
            Api_PortRegistry_Port = (uint8_t *) &PORTA;
            break;
        case API_PORTREGISTRY_PORTB:
            Api_PortRegistry_Port = (uint8_t *) &PORTB;
            break;
        case API_PORTREGISTRY_PORTC:
            Api_PortRegistry_Port = (uint8_t *) &PORTC;
            break;
    }
}

void Api_PortRegistry_SetPin(uint8_t pins, uint8_t type)
{
    switch (type) {
        case API_PORTREGISTRY_SETZERO:
            pins = ~pins;
            (*Api_PortRegistry_Port) &= pins;
            break;
        case API_PORTREGISTRY_SETONE:
            (*Api_PortRegistry_Port) |= pins;
            break;
    }
}