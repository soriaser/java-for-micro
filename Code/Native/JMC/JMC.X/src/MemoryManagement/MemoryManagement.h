/* 
 * File:   MemoryManagement.h
 * Author: Sergio Soria
 *
 * Created on 5 de septiembre de 2014, 17:48
 */

#ifndef MEMORYMANAGEMENT_H
#define	MEMORYMANAGEMENT_H

#ifdef	__cplusplus
extern "C" {
#endif

#if (PLATFORM == PLATFORM_PIC18F4520)
#include "MemoryManagement_PIC18F4520.h"
#elif (PLATFORM == PLATFORM_PIC16F877)
#include "MemoryManagement_PIC16F877.h"
#endif // PLATFORM

extern void Mm_CopyRam(uint8_t *destination, uint8_t *source, uint16_t size);
extern uint8_t  Mm_GetU08(mm_address_t address);
extern uint16_t Mm_GetU16(mm_address_t address);
extern void Mm_SetU08(mm_address_t address, uint8_t value);
extern void Mm_SetU16(mm_address_t address, uint16_t value);

#ifdef	__cplusplus
}
#endif

#endif	/* MEMORYMANAGEMENT_H */

