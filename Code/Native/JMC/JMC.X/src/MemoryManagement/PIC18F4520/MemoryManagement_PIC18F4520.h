/* 
 * File:   MemoryManagement.h
 * Author: Sergio Soria
 *
 * Created on 5 de septiembre de 2014, 17:48
 */

#ifndef MEMORYMANAGEMENT_PIC18F4520_H
#define	MEMORYMANAGEMENT_PIC18F4520_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "Common.h"

extern void Mm_ReadNVM(uint32_t address, uint32_t bytes, uint8_t *data);
extern void Mm_WriteNVM(uint32_t address, uint32_t bytes, uint8_t *data);

#ifdef	__cplusplus
}
#endif

#endif	/* MEMORYMANAGEMENT_PIC18F4520_H */

