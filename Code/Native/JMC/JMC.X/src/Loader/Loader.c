#include "Common.h"

#include "JMC.h"
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
#define LOADER_STATE_PROCESS_DATA_TAG           0x01
#define LOADER_STATE_PROCESS_DATA_LENGTH        0x02
#define LOADER_STATE_PROCESS_DATA_LOAD_CLASS    0x20
#define LOADER_STATE_PROCESS_DATA_LOAD_FIELDS   0x10
#define LOADER_STATE_PROCESS_DATA_LOAD_METHODS  0x08
#define LOADER_STATE_PROCESS_DATA_LOAD_F_OR_M   0x04

#define LENGTH_FORMAT_2B_1ST_BYTE   0x80
#define LENGTH_FORMAT_2B            0x01
#define LENGTH_FORMAT_1B            0x00

#define LOADER_VERSION_MSB 0x00
#define LOADER_VERSION_LSB 0x01

uint8_t Loader_CmdReceived = 0x00;

uint8_t Loader_CurrentValue = 0xFF;

uint8_t Loader_LoaderState = LOADER_STATE_IDLE;

uint16_t Loader_InputOffset = 0;

uint16_t Loader_InputCmdLength = 0;

uint16_t Loader_InputTlvLength = 0;

#define Loader_IsTagProcessed() \
    (Loader_LoaderState & LOADER_STATE_PROCESS_DATA_TAG)

#define Loader_IslengthProcessed() \
    (Loader_IsTagProcessed() && \
    (Loader_LoaderState & LOADER_STATE_PROCESS_DATA_LENGTH))

#define Loader_SetProcessTag() \
    Loader_LoaderState &= ~LOADER_STATE_PROCESS_DATA_TAG; \
    Loader_LoaderState &= ~LOADER_STATE_PROCESS_DATA_LENGTH;

#define Loader_SetProcessLength() \
    Loader_LoaderState |= LOADER_STATE_PROCESS_DATA_TAG; \
    Loader_LoaderState &= ~LOADER_STATE_PROCESS_DATA_LENGTH;

#define Loader_SetProcessData() \
    Loader_LoaderState |= LOADER_STATE_PROCESS_DATA_TAG; \
    Loader_LoaderState |= LOADER_STATE_PROCESS_DATA_LENGTH;

void Loader_ProcessLength(uint8_t format)
{
    // If first byte has been processed...
    if (Loader_InputTlvLength & LENGTH_FORMAT_2B_1ST_BYTE) {
        // First byte flag is removed
        Loader_InputTlvLength &= ~LENGTH_FORMAT_2B_1ST_BYTE;
        Loader_InputTlvLength  = (Loader_InputTlvLength << 8) & 0xFF00;
        Loader_InputTlvLength |= (Loader_CurrentValue & 0x00FF);

        Loader_SetProcessData();
    } else {
        // If it is the first byte
        Loader_InputTlvLength = (Loader_CurrentValue & 0x00FF);

        switch (format) {
            case LENGTH_FORMAT_1B:
                Loader_SetProcessData();
                break;
            case LENGTH_FORMAT_2B:
                Loader_InputTlvLength |= LENGTH_FORMAT_2B_1ST_BYTE;
                break;
        }
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

uint8_t Loader_ProcessCommandLoadField(void)
{
    if (!Loader_IsTagProcessed()) {
        if (JMC_TAG_FIELD != Loader_CurrentValue) {
            return 0x01;
        }

        Loader_SetProcessLength();
    } else if (!Loader_IslengthProcessed()) {
        if (0x01 != Loader_CurrentValue) {
            return 0x01;
        }

        Loader_SetProcessData();
    } else {
        Mm_SetU08((uint32_t) &Jmc_Fields[Jmc_CurrentOffsetFields].id,
                Loader_CurrentValue);
        Mm_SetU16((uint32_t) &Jmc_Fields[Jmc_CurrentOffsetFields].value,
                (uint16_t) 0xFFFF);

        // Increase fields in class
        Mm_SetU08((uint32_t) &Jmc_Classes[Jmc_CurrentOffsetClasses].fields,
                (uint8_t) (Jmc_Classes[Jmc_CurrentOffsetClasses].fields + 1));

        // Increase offset
        Mm_SetU16((uint32_t) &Jmc_CurrentOffsetFields,
                (uint16_t) (Jmc_CurrentOffsetFields + 1));
    }

    Loader_InputTlvLength--;
    if (!Loader_InputTlvLength) {
        Loader_LoaderState &= ~LOADER_STATE_PROCESS_DATA_LOAD_F_OR_M;
        Loader_LoaderState |= LOADER_STATE_PROCESS_DATA_LOAD_CLASS;
    }

    return 0x00;
}

uint8_t Loader_ProcessCommandLoadFields(void)
{
    if (Loader_LoaderState & LOADER_STATE_PROCESS_DATA_LOAD_F_OR_M) {
        return Loader_ProcessCommandLoadField();
    } else {
        if (!Loader_IslengthProcessed()) {
            Loader_ProcessLength(LENGTH_FORMAT_1B);

            // Next step: field tag
            Loader_SetProcessTag();
            Loader_LoaderState |= LOADER_STATE_PROCESS_DATA_LOAD_F_OR_M;

            if (0x00 < Loader_InputTlvLength) {
                // Store offset in JMC class
                Mm_SetU16((uint32_t)
                        &Jmc_Classes[Jmc_CurrentOffsetClasses].fieldsOffset,
                        (uint16_t) Jmc_CurrentOffsetFields);
            }
        }
    }

    return 0x00;
}

uint8_t Loader_ProcessCommandLoadClass(void)
{
    if (!Loader_IsTagProcessed()) {
        if (Loader_CurrentValue != JMC_TAG_CLASS) {
            return 0x01;
        }

        Loader_SetProcessLength();
    } else if (!Loader_IslengthProcessed()) {
        Loader_ProcessLength(LENGTH_FORMAT_2B);

        // Second byte length has been processed
        if (Loader_IslengthProcessed()) {
            Loader_SetProcessData();
        }
    } else {
        switch (Loader_CurrentValue) {
            case JMC_TAG_FIELDS:
                Loader_LoaderState |= LOADER_STATE_PROCESS_DATA_LOAD_FIELDS;
                break;
            case JMC_TAG_METHODS:
                Loader_LoaderState |= LOADER_STATE_PROCESS_DATA_LOAD_METHODS;
                break;
            default:
                return 0x01;
        }

        Loader_LoaderState &= ~LOADER_STATE_PROCESS_DATA_LOAD_CLASS;
        Loader_SetProcessLength();
    }

    return 0x00;
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

                // Next step to process id class tag
                Loader_LoaderState |= LOADER_STATE_PROCESS_DATA_LOAD_CLASS;
                Loader_SetProcessTag();
                break;
            default:
                if (Loader_LoaderState & LOADER_STATE_PROCESS_DATA_LOAD_CLASS) {
                    error = Loader_ProcessCommandLoadClass();
                } else if (Loader_LoaderState &
                        LOADER_STATE_PROCESS_DATA_LOAD_FIELDS) {
                    error = Loader_ProcessCommandLoadFields();
                } else if (Loader_LoaderState &
                        LOADER_STATE_PROCESS_DATA_LOAD_METHODS) {
                    // TODO: Process Methods
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
    }

    Loader_InputOffset++;
}

void Loader_SendError(uint16_t error)
{
    SerialPort_DisableRx();
    SerialPort_Send((uint8_t) (error >> 8));
    SerialPort_Send((uint8_t) (error));

    // Reset state
    Loader_LoaderState = LOADER_STATE_IDLE;
}
