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

extern const unsigned char Loader_IsLoaderEnabled;

extern volatile unsigned char Loader_CmdReceived;

extern volatile unsigned char Loader_CurrentValue;

extern volatile unsigned char Loader_LoaderState;

extern volatile unsigned short Loader_InputOffset;

extern volatile unsigned short Loader_InputCmdLength;

extern void Loader_ISR(void);

extern void Loader_ProcessCommandLoad(void);

extern void Loader_ProcessCommandData(void);

extern void Loader_ProcessCommandHeader(void);

extern void Loader_ProcessLoadHeader(void);

extern void Loader_SendError(unsigned short error);

#ifdef	__cplusplus
}
#endif

#endif	/* LOADER_H */

