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

#include "Common.h"

#define Timer_T0_Init() \
    INTCON = 0xC0; \
    TMR0IE = 1; \
    T0CON = 0x40

#define Timer_T0_Reset() (TMR0 = 0)

#define Timer_T0_Start() (TMR0ON = 1)

#define Timer_T0_Stop() \
    TMR0ON = 0; \
    Timer_T0_Reset()
    

void Timer_T0_ISR(void);


#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_H */

