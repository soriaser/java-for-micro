/* 
 * File:   MemoryManagement.h
 * Author: Sudi
 *
 * Created on 15 de agosto de 2014, 13:30
 */

#ifndef MEMORYMANAGEMENT_H
#define	MEMORYMANAGEMENT_H

#ifdef	__cplusplus
extern "C" {
#endif

extern unsigned char Mm_GetByteNVM(unsigned char *byte);

extern void Mm_SetByteNVM(unsigned char *byte, unsigned char value);

extern void Mm_SetBytesNVM(unsigned short *bytes, unsigned short value);

#ifdef	__cplusplus
}
#endif

#endif	/* MEMORYMANAGEMENT_H */

