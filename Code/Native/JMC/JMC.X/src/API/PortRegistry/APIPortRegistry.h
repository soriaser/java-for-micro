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

#define API_PORTREGISTRY_PORTA      0x00
#define API_PORTREGISTRY_PORTB      0x01
#define API_PORTREGISTRY_PORTC      0x02
#define API_PORTREGISTRY_UNKNOWN    0xFF

extern uint8_t Api_PortRegistry_Port;

#define Api_PortRegistry_GetPortRegistry(port) \
    (Api_PortRegistry_Port = (uint8_t) port)

#ifdef	__cplusplus
}
#endif

#endif	/* APIPORTREGISTRY_H */

