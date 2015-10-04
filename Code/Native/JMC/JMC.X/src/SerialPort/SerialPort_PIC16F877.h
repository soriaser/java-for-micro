/* 
 * File:   SerialPort.h
 * Author: Sergio Soria
 *
 * Created on 12 de agosto de 2014, 17:06
 */

#ifndef SERIALPORT_PIC16F877_H
#define SERIALPORT_PIC16F877_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Common.h"

#define SerialPort_DisableRx() (RCIE = 0)

#define SerialPort_EnableRx() (RCIE = 1)

#define SerialPort_Receive() (RCREG)

extern void SerialPort_Init(void);

extern void SerialPort_ISR(void);

extern void SerialPort_Send(uint8_t byte);

#ifdef __cplusplus
}
#endif

#endif /* SERIALPORT_PIC16F877_H */

