/* 
 * File:   Platform_PIC16F877.h
 * Author: Sergio Soria
 *
 * Created on 05 de septiembre de 2014, 17:13
 */

#ifndef PLATFORM_PIC16F877_H
#define PLATFORM_PIC16F877_H

#ifdef __cplusplus
extern "C" {
#endif

#include <xc.h>

#pragma config FOSC     = HS
#pragma config CP       = OFF
#pragma config CPD      = OFF
#pragma config WRT      = ON
#pragma config WDTE     = OFF
#pragma config BOREN    = OFF
#pragma config LVP      = OFF

#define _XTAL_FREQ 4000000
#define BAUDRATE 2400
#define JAVACLASS_MAX_SIZE_DATA     512
#define JVM_MAX_SIZE_HEAP           80

#ifdef __cplusplus
}
#endif

#endif /* PLATFORM_PIC16F877_H */