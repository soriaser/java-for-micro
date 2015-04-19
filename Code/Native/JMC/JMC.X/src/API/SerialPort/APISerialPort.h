/* 
 * File:   APISerialPort.h
 * Author: Sergio Soria
 *
 * Created on 15 de marzo de 2015, 19:14
 */

#ifndef APISERIALPORT_H
#define	APISERIALPORT_H

#ifdef	__cplusplus
extern "C" {
#endif

extern uint8_t Api_SerialPort_Events;

#define Api_SerialPort_SetEvent(event) (Api_SerialPort_Events = event)

void API_SerialPort_Send(uint8_t *data, uint16_t offset, uint16_t size);


#ifdef	__cplusplus
}
#endif

#endif	/* APISERIALPORT_H */

