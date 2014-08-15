/* 
 * File:   Loader.h
 * Author: Sergio Soria
 *
 * Created on 12 de agosto de 2014, 17:00
 */

#ifndef LOADER_H
#define	LOADER_H

#ifdef	__cplusplus
extern "C" {
#endif

#define LOADER_INPUT_ARRAY_MAX_SIZE 10

#define LOADER_DISABLED     0x00

#define LOADER_ENABLED      0x01

extern unsigned char Loader_InputArrayPointer;

extern unsigned char Loader_IsLoaderEnabled;

extern volatile unsigned char Loader_InputArray[LOADER_INPUT_ARRAY_MAX_SIZE];

extern void Loader_ISR(void);

#ifdef	__cplusplus
}
#endif

#endif	/* LOADER_H */

