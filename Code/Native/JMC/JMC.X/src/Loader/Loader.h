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

#define LOADER_DISABLED         0x00
#define LOADER_ENABLED          0x01

#define LOADER_STATE_IDLE           0x00
#define LOADER_STATE_PENDING        0x80
#define LOADER_STATE_PROCESS_MASK   0x40
#define LOADER_STATE_PROCESS        0x00
#define LOADER_STATE_PROCESS_DATA   0x40

#define LOADER_WAIT_BYTE        0x60
#define LOADER_CONTINUE_BYTE    0x61

extern NVMDATA uint8_t Loader_IsLoaderEnabled;

extern uint8_t Loader_LoaderState;

extern uint8_t Loader_CurrentValue;

#define Loader_SetToIdle() \
    Loader_LoaderState &= ~LOADER_STATE_PENDING;

extern void Loader_ISR(void);

extern void Loader_SendResponse(uint16_t error);

extern void Loader_Disable(void);

#ifdef	__cplusplus
}
#endif

#endif	/* LOADER_H */

