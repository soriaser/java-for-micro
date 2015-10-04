/* 
 * File:   Timer.h
 * Author: Sergio Soria
 *
 * Created on 16 de septiembre de 2014, 18:44
 */

#ifndef TIMER_H
#define	TIMER_H

#ifdef	__cplusplus
extern "C" {
#endif

#if (PLATFORM == PLATFORM_PIC18F4520)
#include "Timer_PIC18F4520.h"
#elif (PLATFORM == PLATFORM_PIC16F877)
#include "Timer_PIC16F877.h"
#endif // PLATFORM

extern void Timer_Clear();

extern void Timer_Disable();

extern void Timer_Enable();

extern void Timer_GetTimer(uint8_t timer);

extern uint16_t Timer_Read();

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_H */

