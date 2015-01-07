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

#define API_PORTREGISTRY_EVENT_INT0 0x00
#define API_PORTREGISTRY_EVENT_INT1 0x01

#define API_PORTREGISTRY_PORTA      0x00
#define API_PORTREGISTRY_PORTB      0x01
#define API_PORTREGISTRY_PORTC      0x02

#define API_PORTREGISTRY_SETZERO    0x00
#define API_PORTREGISTRY_SETONE     0x01
#define API_PORTREGISTRY_SETOUTPUT  0x02
#define API_PORTREGISTRY_SETINPUT   0x03

#define Api_PortRegistry_SetInputPin(pin) \
    Api_PortRegistry_SetPin((0x01 << pin), API_PORTREGISTRY_SETINPUT)

#define Api_PortRegistry_SetOutputPin(pin) \
    Api_PortRegistry_SetPin((0x01 << pin), API_PORTREGISTRY_SETOUTPUT)

#define Api_PortRegistry_SetPinToOne(pin) \
    Api_PortRegistry_SetPin((0x01 << pin), API_PORTREGISTRY_SETONE)

#define Api_PortRegistry_SetPinToZero(pin) \
    Api_PortRegistry_SetPin((0x01 << pin), API_PORTREGISTRY_SETZERO)

extern uint8_t *Api_PortRegistry_Port;

extern uint8_t *Api_PortRegistry_Tris;

extern uint8_t Api_PortRegistry_Events;

extern void Api_PortRegistry_GetPortRegistry(uint8_t port);

extern void Api_PortRegistry_SetEvent(uint8_t event);

extern void Api_PortRegistry_SetPin(uint8_t pin, uint8_t type);

#ifdef	__cplusplus
}
#endif

#endif	/* APIPORTREGISTRY_H */

