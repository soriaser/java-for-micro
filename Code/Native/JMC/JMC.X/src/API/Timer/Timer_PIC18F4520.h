/* 
 * File:   Timer_PIC18F4520.h
 * Author: Sergio Soria
 *
 * Created on 1 de junio de 2015, 16:24
 */

#ifndef TIMER_PIC18F4520_H
#define	TIMER_PIC18F4520_H

#ifdef	__cplusplus
extern "C" {
#endif

extern void Timer_GetTimer(uint8_t timer);

extern void Timer_Clear();

extern void Timer_Disable();

extern void Timer_Enable();

extern void Timer_GetTimer(uint8_t timer);

extern uint16_t Timer_Read();

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_PIC18F4520_H */

