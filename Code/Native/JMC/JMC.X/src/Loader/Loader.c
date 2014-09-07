#include "Common.h"

#include "Loader.h"
#include "MemoryManagement.h"
#include "SerialPort.h"

#define LOADER_CMD_CLA 0x00

#define LOADER_CMD_CLA_OFFSET   0
#define LOADER_CMD_INS_OFFSET   LOADER_CMD_CLA_OFFSET + 1
#define LOADER_CMD_PR1_OFFSET   LOADER_CMD_INS_OFFSET + 1
#define LOADER_CMD_PR2_OFFSET   LOADER_CMD_PR1_OFFSET + 1
#define LOADER_CMD_LEN_OFFSET   LOADER_CMD_PR2_OFFSET + 1
#define LOADER_CMD_DATA_OFFSET  LOADER_CMD_LEN_OFFSET + 2

#define LOADER_CMD_LOAD_INS 0xA0

#define LOADER_CMD_LOAD_VERSION_OFFSET  LOADER_CMD_DATA_OFFSET

#define LOADER_ERROR_CLA_NOT_SUPPORTED  0x6E00
#define LOADER_ERROR_INS_NOT_SUPPORTED  0x6D00
#define LOADER_ERROR_WRONG_DATA         0x6A80

#define LOADER_STATE_IDLE                       0x00
#define LOADER_STATE_PROCESS_DATA               0x80
#define LOADER_STATE_PROCESS_DATA_LOAD_CMD_TAG  LOADER_STATE_PROCESS_DATA | 0x01
#define LOADER_STATE_PROCESS_DATA_LOAD_CMD_LEN  LOADER_STATE_PROCESS_DATA | 0x02
#define LOADER_STATE_END                        0xFF

#define LOADER_VERSION_MSB 0x00
#define LOADER_VERSION_LSB 0x01

uint8_t Loader_CmdReceived = 0x00;

uint8_t Loader_CurrentValue = 0xFF;

uint8_t Loader_LoaderState = LOADER_STATE_IDLE;

uint16_t Loader_InputOffset = 0;

uint16_t Loader_InputCmdLength = 0x00;

void Loader_ISR(void)
{
    Loader_CurrentValue = RCREG;

    switch (Loader_LoaderState & 0x80) {
        case LOADER_STATE_IDLE:
            Loader_ProcessCommandHeader();
            break;
        case LOADER_STATE_PROCESS_DATA:
            Loader_ProcessCommandData();
            break;
        case LOADER_STATE_END:
            Mm_SetU08((uint32_t *) &Loader_IsLoaderEnabled, LOADER_DISABLED);
            break;
    }

    Loader_InputOffset++;
}

void Loader_ProcessCommandLoad(void)
{
    uint8_t error = 0x00;

    if (Loader_InputCmdLength + LOADER_CMD_DATA_OFFSET >= Loader_InputOffset) {
        switch (Loader_InputOffset) {
            case LOADER_CMD_LOAD_VERSION_OFFSET:
                error = (LOADER_VERSION_MSB != Loader_CurrentValue);
                break;
            case LOADER_CMD_LOAD_VERSION_OFFSET + 1:
                error = (LOADER_VERSION_LSB != Loader_CurrentValue);
                break;
            default:
                switch (Loader_LoaderState) {
                    case LOADER_STATE_PROCESS_DATA_LOAD_CMD_TAG:
                        break;
                }
                break;
        }
    }

    if (0x00 < error) {
        Loader_SendError(LOADER_ERROR_WRONG_DATA);
    }
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

void Loader_SendError(uint16_t error)
{
    SerialPort_DisableRx();
    SerialPort_Send((uint8_t) (error >> 8));
    SerialPort_Send((uint8_t) (error));
}
