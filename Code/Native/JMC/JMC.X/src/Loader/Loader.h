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

extern uint8_t Loader_CmdReceived;

extern uint8_t Loader_CurrentValue;

extern uint8_t Loader_LoaderState;

extern uint16_t Loader_InputOffset;

extern uint16_t Loader_InputCmdLength;

extern void Loader_ISR(void);

extern void Loader_ProcessCommandLoad(void);

extern void Loader_ProcessCommandData(void);

extern void Loader_ProcessCommandHeader(void);

extern void Loader_ProcessLoadHeader(void);

extern void Loader_SendError(uint16_t error);

#ifdef	__cplusplus
}
#endif

#endif	/* LOADER_H */

