/* 
 * File:   SerialPort.h
 * Author: Sergio Soria
 *
 * Created on 12 de agosto de 2014, 17:06
 */

#ifndef SERIALPORT_H
#define	SERIALPORT_H

#ifdef	__cplusplus
extern "C" {
#endif

#if (PLATFORM == PLATFORM_PIC18F4520)
#include "SerialPort_PIC18F4520.h"
#elif (PLATFORM == PLATFORM_PIC16F877)
#include "SerialPort_PIC16F877.h"
#endif // PLATFORM

extern uint8_t SerialPort_CurrentValueRx;

#ifdef	__cplusplus
}
#endif

#endif	/* SERIALPORT_H */

