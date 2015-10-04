/* 
 * File:   Platform.h
 * Author: Sergio Soria
 *
 * Created on 05 de septiembre de 2014, 17:13
 */

#ifndef PLATFORM_H
#define	PLATFORM_H

#ifdef	__cplusplus
extern "C" {
#endif

#if (PLATFORM == PLATFORM_PIC18F4520)
#include "Platform_PIC18F4520.h"
#elif (PLATFORM == PLATFORM_PIC16F877)
#include "Platform_PIC16F877.h"
#endif // PLATFORM

#ifdef	__cplusplus
}
#endif

#endif	/* PLATFORM_H */