/* 
 * File:   APIPortRegistry.h
 * Author: Sergio Soria
 *
 * Created on 4 de enero de 2015, 23:42
 */

#ifndef APIPORTREGISTRY_H
#define	APIPORTREGISTRY_H

#ifdef	__cplusplus
extern "C" {
#endif

#if (PLATFORM == PLATFORM_PIC18F4520)
#include "Port_PIC18F4520.h"
#endif // PLATFORM

#define API_PORTREGISTRY_EVENT_INT0 0x01
#define API_PORTREGISTRY_EVENT_INT1 0x02

#define API_PORTREGISTRY_PORTA      0x00
#define API_PORTREGISTRY_PORTB      0x01
#define API_PORTREGISTRY_PORTC      0x02

#define API_PORTREGISTRY_SETZERO    0x00
#define API_PORTREGISTRY_SETONE     0x01
#define API_PORTREGISTRY_SETOUTPUT  0x02
#define API_PORTREGISTRY_SETINPUT   0x03
#define API_PORTREGISTRY_SETIO      0x04
#define API_PORTREGISTRY_SETPINS    0x05

#define Api_PortRegistry_SetInputPin(pin) \
    Port_SetPin((0x01 << pin), API_PORTREGISTRY_SETINPUT)

#define Api_PortRegistry_SetIO(pins) \
    Port_SetPin(pins, API_PORTREGISTRY_SETIO)

#define Api_PortRegistry_SetOutputPin(pin) \
    Port_SetPin((0x01 << pin), API_PORTREGISTRY_SETOUTPUT)

#define Api_PortRegistry_SetPins(pins) \
    Port_SetPin(pins, API_PORTREGISTRY_SETPINS)

#define Api_PortRegistry_SetPinToOne(pin) \
    Port_SetPin((0x01 << pin), API_PORTREGISTRY_SETONE)

#define Api_PortRegistry_SetPinToZero(pin) \
    Port_SetPin((0x01 << pin), API_PORTREGISTRY_SETZERO)

#define Api_PortRegistry_GetPortRegistry(port) \
    Port_GetPortRegistry(port)

#ifdef	__cplusplus
}
#endif

#endif	/* APIPORTREGISTRY_H */

