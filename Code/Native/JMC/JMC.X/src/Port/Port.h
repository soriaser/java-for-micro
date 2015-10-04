/* 
 * File:   Port.h
 * Author: Sergio Soria
 *
 * Created on 7 de enero de 2015, 13:29
 */

#ifndef PORT_H
#define PORT_H

#ifdef __cplusplus
extern "C" {
#endif

#if (PLATFORM == PLATFORM_PIC18F4520)
#include "Port_PIC18F4520.h"
#elif (PLATFORM == PLATFORM_PIC16F877)
#include "Port_PIC16F877.h"
#endif // PLATFORM

#ifdef __cplusplus
}
#endif

#endif /* PORT_H */

