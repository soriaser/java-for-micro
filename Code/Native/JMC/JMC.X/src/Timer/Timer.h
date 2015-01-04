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

#define TIMER0_OVERFLOW_USEC ((256 * 1000000) / FCPU)

#define Timer_T0_Reset() (TMR0 = 0)

#define Timer_T0_Start() (TMR0ON = 1)

#define Timer_T0_Stop() \
    TMR0ON = 0; \
    Timer_T0_Reset()
    
extern void Timer_T0_Init(uint8_t interruption);

extern void Timer_T0_ISR(void);


#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_H */

