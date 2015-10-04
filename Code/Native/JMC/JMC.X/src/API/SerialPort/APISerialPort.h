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

#include "SerialPort.h"

#define API_SERIALPORT_EVENT_RECEIVED_BYTE 0x04

extern uint8_t API_SerialPort_Receive(void);

extern void API_SerialPort_Send(uint8_t *data, uint16_t offset, uint16_t size);

#ifdef	__cplusplus
}
#endif

#endif	/* APISERIALPORT_H */

