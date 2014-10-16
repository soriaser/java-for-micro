#include "Common.h"
#include "JVM.h"
#include "Loader.h"
#include "MemoryManagement.h"
#include "SerialPort.h"

#define LOADER_CMD_CLA                      0x00
#define LOADER_CMD_INS_LOAD                 0x10
#define LOADER_CMD_INS_REMOVE               0x11

#define LOADER_ACK_CONTINUE                 0x61
#define LOADER_ERROR_CLA_NOT_SUPPORTED      0x91
#define LOADER_ERROR_INS_NOT_SUPPORTED      0x92
#define LOADER_ERROR_WRONG_DATA             0x93
#define LOADER_NO_ERROR                     0x80

#define LOADER_CMD_STATE_PROCESS_CLA        0x00
#define LOADER_CMD_STATE_PROCESS_INS \
    (LOADER_CMD_STATE_PROCESS_CLA + 1)
#define LOADER_CMD_STATE_PROCESS_LENGTH_1B \
    (LOADER_CMD_STATE_PROCESS_INS + 1)
#define LOADER_CMD_STATE_PROCESS_LENGTH_2B \
    (LOADER_CMD_STATE_PROCESS_LENGTH_1B + 1)
#define LOADER_CMD_STATE_PROCESS_DATA \
    (LOADER_CMD_STATE_PROCESS_LENGTH_2B + 1)
#define LOADER_CMD_STATE_PROCESS_DATA_END \
    (LOADER_CMD_STATE_PROCESS_DATA + 1)

uint16_t Loader_CmdLength = 0;

uint16_t Loader_CmdDataOffset = 0;

uint8_t  Loader_Cmd = 0x00;

uint8_t  Loader_CmdProcessingState = LOADER_CMD_STATE_PROCESS_CLA;

uint8_t  Loader_State = LOADER_STATE_IDLE;

uint8_t Loader_ProcessCommandLoad(uint8_t value)
{
    Mm_SetU08((uint32_t) &Jvm_ClassData[Loader_CmdDataOffset], value);
    Loader_CmdDataOffset++;

    if (Loader_CmdLength == Loader_CmdDataOffset) {
        // Increase command processing state by one in order ot indicate end
        // of processing
        Loader_CmdProcessingState++;
        // Reset offset
        Loader_CmdDataOffset = 0;
        // Store length of java class
        Mm_SetU16((uint32_t) &Jvm_ClassDataSize, Loader_CmdLength);
        // Loader is disabled until java application is removed
        Mm_SetU08((uint32_t) &Loader_IsLoaderEnabled, LOADER_DISABLED);
        // Successfully finished
        return LOADER_NO_ERROR;
    }

    return LOADER_ACK_CONTINUE;
}

void Loader_ProcessCommand(uint8_t value)
{
    uint8_t response = LOADER_ACK_CONTINUE;

    switch (Loader_CmdProcessingState) {
        case LOADER_CMD_STATE_PROCESS_CLA:
            if (LOADER_CMD_CLA != value) {
                response = LOADER_ERROR_CLA_NOT_SUPPORTED;
            }
            break;
        case LOADER_CMD_STATE_PROCESS_INS:
            switch (value) {
                case LOADER_CMD_INS_LOAD:
                    Loader_Cmd = LOADER_CMD_INS_LOAD;
                    break;
                case LOADER_CMD_INS_REMOVE:
                    Loader_Cmd = LOADER_CMD_INS_REMOVE;
                    // TODO: Process remove directly. Length is ignored
                    break;
                default:
                    response = LOADER_ERROR_INS_NOT_SUPPORTED;
                    break;
            }
            break;
        case LOADER_CMD_STATE_PROCESS_LENGTH_1B:
            Loader_CmdLength = value;
            Loader_CmdLength = Loader_CmdLength << 8;
            break;
        case LOADER_CMD_STATE_PROCESS_LENGTH_2B:
            Loader_CmdLength += value;
            break;
        case LOADER_CMD_STATE_PROCESS_DATA:
            switch (Loader_Cmd) {
                case LOADER_CMD_INS_LOAD:
                    response = Loader_ProcessCommandLoad(value);
                    break;
            }
            break;
    }

    // Increase command processing state if header is being processed
    if (LOADER_CMD_STATE_PROCESS_DATA > Loader_CmdProcessingState) {
        Loader_CmdProcessingState++;
    }

    // Change to idle state
    Loader_State = LOADER_STATE_IDLE;
    // Rx was disabled when bytes is received, now it is enabled again to
    // allow receive new bytes
    SerialPort_EnableRx();

    // If process command has finished or some error happened, reset state.
    if ((LOADER_CMD_STATE_PROCESS_DATA_END == Loader_CmdProcessingState)
            || (LOADER_ACK_CONTINUE != response)) {
        // Reset command state
        Loader_CmdProcessingState = LOADER_CMD_STATE_PROCESS_CLA;
    }

    // Send ACK indicating that we are ready to receive another byte
    SerialPort_Send(response);
}
