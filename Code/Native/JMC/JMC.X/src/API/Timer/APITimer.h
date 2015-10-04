/* 
 * File:   APITimer.h
 * Author: Sergio Soria
 *
 * Created on 1 de junio de 2015, 16:16
 */

#ifndef APITIMER_H
#define	APITIMER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "Timer.h"

#define API_TIMER_TIMER_0   0x00
#define API_TIMER_TIMER_1   0x01
#define API_TIMER_UNKNOWN   0xFF

extern uint8_t Api_Timer_CurrentTimer;

#define Api_Timer_GetTimer(timer) (Timer_GetTimer(timer))

#define Api_Timer_Clear() (Timer_Clear())

#define Api_Timer_Disable() (Timer_Disable())

#define Api_Timer_Enable() (Timer_Enable())

#define Api_Timer_Read() (Timer_Read())

#ifdef	__cplusplus
}
#endif

#endif	/* APITIMER_H */

