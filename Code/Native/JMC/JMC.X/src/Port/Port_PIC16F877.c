#include "Common.h"
#include "APIPortRegistry.h"
#include "Port_PIC16F877.h"

#if (PLATFORM == PLATFORM_PIC16F877)

uint8_t *PortRegistry_Port = NULL;

uint8_t *PortRegistry_Tris = NULL;

void Port_ClearEvent(uint8_t event)
{
    switch (event) {
        case API_PORTREGISTRY_EVENT_INT0:
            // Set INT0 as input
            TRISB = 0x00 | (TRISB & 0xFE);
            // Enable INT0 interruption but interrupt is not thrown.
            // Interrupt should be checked manually
            INTCON = 0x00 | (INTCON & 0xEF);
            break;
    }
}

void Port_GetPortRegistry(uint8_t port)
{
    switch (port) {
        case API_PORTREGISTRY_PORTA:
            PortRegistry_Port = (uint8_t *) &PORTA;
            PortRegistry_Tris = (uint8_t *) &TRISA;
            break;
        case API_PORTREGISTRY_PORTB:
            PortRegistry_Port = (uint8_t *) &PORTB;
            PortRegistry_Tris = (uint8_t *) &TRISB;
            break;
        case API_PORTREGISTRY_PORTC:
            PortRegistry_Port = (uint8_t *) &PORTC;
            PortRegistry_Tris = (uint8_t *) &TRISC;
            break;
    }
}

void Port_SetEvent(uint8_t event)
{
    switch (event) {
        case API_PORTREGISTRY_EVENT_INT0:
            // Set INT0 as input
            TRISB |= 0x01;
            // Enable INT0 interruption but interrupt is not thrown.
            // Interrupt should be checked manually
            INTCON |= 0x10;
            break;
    }
}

void Port_SetPin(uint8_t pins, uint8_t type)
{
    switch (type) {
        case API_PORTREGISTRY_SETZERO:
            pins = ~pins;
            (*PortRegistry_Port) &= pins;
            break;
        case API_PORTREGISTRY_SETOUTPUT:
            pins = ~pins;
            (*PortRegistry_Tris) &= pins;
            break;
        case API_PORTREGISTRY_SETONE:
            (*PortRegistry_Port) |= pins;
            break;
        case API_PORTREGISTRY_SETINPUT:
            (*PortRegistry_Tris) |= pins;
            break;
        case API_PORTREGISTRY_SETIO:
            (*PortRegistry_Tris) = pins;
            break;
        case API_PORTREGISTRY_SETPINS:
            (*PortRegistry_Port) = pins;
            break;
    }
}

#endif //(PLATFORM == PLATFORM_PIC16F877)
