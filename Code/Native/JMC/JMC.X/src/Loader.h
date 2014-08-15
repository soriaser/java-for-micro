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

#define LOADER_CMD_CLA_OFFSET   0
#define LOADER_CMD_INS_OFFSET   1
#define LOADER_CMD_LEN_OFFSET   4
#define LOADER_CMD_DATA_OFFSET  6

#define LOADER_CMD_LOAD_CLA 0x00
#define LOADER_CMD_LOAD_INS 0xA0

#define LOADER_DISABLED     0x00
#define LOADER_ENABLED      0x01

#define LOADER_STATE_IDLE           0x00
#define LOADER_STATE_PROCESS_DATA   0x01

#define LOADER_ERROR_CLA_NOT_SUPPORTED  0x6E00
#define LOADER_ERROR_INS_NOT_SUPPORTED  0x6D00

extern const unsigned char Loader_IsLoaderEnabled;

extern volatile unsigned char Loader_CurrentValue;

extern volatile unsigned char Loader_InputOffset;

extern volatile unsigned char Loader_LoaderState;

extern volatile unsigned short Loader_InputCmdLength;

extern void Loader_ISR(void);

extern void Loader_ProcessCommandHeader(void);

extern void Loader_ProcessLoadHeader(void);

extern void Loader_SendError(unsigned short error);

#ifdef	__cplusplus
}
#endif

#endif	/* LOADER_H */

