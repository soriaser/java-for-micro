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

typedef uint16_t mm_address_t;

extern void Mm_ReadNVM(mm_address_t address, mm_address_t bytes, uint8_t *data);
extern void Mm_WriteNVM(mm_address_t address, mm_address_t bytes, uint8_t *data);

#ifdef	__cplusplus
}
#endif

#endif	/* MEMORYMANAGEMENT_PIC18F4520_H */

