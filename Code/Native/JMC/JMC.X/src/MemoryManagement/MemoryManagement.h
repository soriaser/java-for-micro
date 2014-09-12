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

#include "Common.h"

extern void Mm_SetU08(uint32_t address, uint8_t value);
extern void Mm_SetU16(uint32_t address, uint16_t value);

#ifdef	__cplusplus
}
#endif

#endif	/* MEMORYMANAGEMENT_H */

