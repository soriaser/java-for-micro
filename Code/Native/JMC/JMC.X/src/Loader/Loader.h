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

#define LOADER_STATE_IDLE       0x00
#define LOADER_STATE_PENDING    0x01

#define LOADER_ACK_WAIT         0x60
#define LOADER_ACK_CONTINUE     0x61

extern NVMDATA uint8_t Loader_IsLoaderEnabled;

extern uint8_t Loader_State;

extern void Loader_ProcessCommand(uint8_t value);

#ifdef	__cplusplus
}
#endif

#endif	/* LOADER_H */

