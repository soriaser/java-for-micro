#include "Common.h"

#include "Loader.h"
#include "MemoryManagement.h"
#include "SerialPort.h"

#define LOADER_CMD_CLA 0x00

#define LOADER_CMD_CLA_OFFSET   0
#define LOADER_CMD_INS_OFFSET   1
#define LOADER_CMD_LEN_OFFSET   4
#define LOADER_CMD_DATA_OFFSET  6

#define LOADER_CMD_LOAD_INS 0xA0

#define LOADER_ERROR_CLA_NOT_SUPPORTED  0x6E00
#define LOADER_ERROR_INS_NOT_SUPPORTED  0x6D00

#define LOADER_STATE_IDLE           0x00
#define LOADER_STATE_PROCESS_DATA   0x01

const unsigned char Loader_IsLoaderEnabled = LOADER_ENABLED;

volatile unsigned char Loader_CmdReceived = 0x00;

volatile unsigned char Loader_CurrentValue = 0xFF;

volatile unsigned char Loader_InputOffset = 0x00;

volatile unsigned char Loader_LoaderState = LOADER_STATE_IDLE;

volatile unsigned short Loader_InputCmdLength = 0x00;

void Loader_ISR(void)
{
    Loader_CurrentValue = RCREG;

    switch (Loader_LoaderState) {
        case LOADER_STATE_IDLE:
            Loader_ProcessCommandHeader();
            break;
        case LOADER_STATE_PROCESS_DATA:
            Loader_ProcessCommandData();
            break;
    }

    Loader_InputOffset++;
}

void Loader_ProcessCommandLoad(void)
{
    // TODO
}

void Loader_ProcessCommandData(void)
{
    switch (Loader_CmdReceived) {
        case LOADER_CMD_LOAD_INS:
            Loader_ProcessCommandLoad();
            break;
    }
}

void Loader_ProcessCommandHeader(void)
{
    switch (Loader_InputOffset) {
        case LOADER_CMD_CLA_OFFSET:
            if (LOADER_CMD_CLA != Loader_CurrentValue) {
                Loader_SendError(LOADER_ERROR_CLA_NOT_SUPPORTED);
            }
            break;
        case LOADER_CMD_INS_OFFSET:
            switch (Loader_CurrentValue) {
                case LOADER_CMD_LOAD_INS:
                    Loader_CmdReceived = Loader_CurrentValue;
                    break;
                default:
                    Loader_SendError(LOADER_ERROR_INS_NOT_SUPPORTED);
                    break;
            }
            break;
        case LOADER_CMD_LEN_OFFSET + 1:
            Loader_LoaderState = LOADER_STATE_PROCESS_DATA;
        case LOADER_CMD_LEN_OFFSET:
            Loader_ProcessLoadHeader();
            break;
    }
}

void Loader_ProcessLoadHeader(void)
{
    switch (Loader_InputOffset) {
        case LOADER_CMD_LEN_OFFSET:
            Loader_InputCmdLength = (Loader_CurrentValue << 8) & 0xFF00;
            break;
        case LOADER_CMD_LEN_OFFSET + 1:
            Loader_InputCmdLength += Loader_CurrentValue;
            break;
    }
}

void Loader_SendError(unsigned short error)
{
    SerialPort_DisableRx();
    SerialPort_Send((unsigned char) (error >> 8));
    SerialPort_Send((unsigned char) (error));
}
