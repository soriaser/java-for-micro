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

#define LOADER_DISABLED     0x00

#define LOADER_ENABLED      0x01

extern NVMDATA uint8_t Loader_IsLoaderEnabled;

extern void Loader_ISR(void);

extern void Loader_SendError(uint16_t error);

#ifdef	__cplusplus
}
#endif

#endif	/* LOADER_H */

