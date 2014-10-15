#include "Common.h"

#include "JMC.h"
#include "Loader.h"
#include "MemoryManagement.h"
#include "SerialPort.h"
#include "Timer.h"

#define LOADER_CMD_CLA 0x00

#define LOADER_CMD_CLA_OFFSET   0
#define LOADER_CMD_INS_OFFSET   LOADER_CMD_CLA_OFFSET + 1
#define LOADER_CMD_DATA_OFFSET  LOADER_CMD_INS_OFFSET + 1

#define LOADER_CMD_LOAD_INS 0xA0

#define LOADER_CMD_LOAD_VERSION_OFFSET  LOADER_CMD_DATA_OFFSET

#define LOADER_ERROR_CLA_NOT_SUPPORTED  0x6E00
#define LOADER_ERROR_INS_NOT_SUPPORTED  0x6D00
#define LOADER_ERROR_WRONG_DATA         0x6A80
#define LOADER_NO_ERROR                 0x9000

#define LOADER_STATE_PROCESS_DATA_LOAD_MASK     0x30
#define LOADER_STATE_PROCESS_DATA_LOAD_CLASS    0x00
#define LOADER_STATE_PROCESS_DATA_LOAD_FIELDS   0x10
#define LOADER_STATE_PROCESS_DATA_LOAD_METHODS  0x20

#define LOADER_STATE_PROCESS_DATA_TAG           0x01
#define LOADER_STATE_PROCESS_DATA_LENGTH        0x02

#define LENGTH_FORMAT_2B_1ST_BYTE   0x80
#define LENGTH_FORMAT_2B            0x01
#define LENGTH_FORMAT_1B            0x00

#define LOADER_VERSION_MSB 0x00
#define LOADER_VERSION_LSB 0x01

uint8_t Loader_CmdReceived = 0x00;

uint8_t Loader_CurrentValue = 0xFF;

uint8_t Loader_LoaderState = LOADER_STATE_IDLE;

uint8_t Loader_FieldsOrMethodsToProcess = 0;

uint16_t Loader_InputOffset = 0;

uint16_t Loader_CodeLength = 0;

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
    if (Loader_CodeLength & LENGTH_FORMAT_2B_1ST_BYTE) {
        // First byte flag is removed
        Loader_CodeLength &= ~LENGTH_FORMAT_2B_1ST_BYTE;
        Loader_CodeLength  = ((Loader_CodeLength << 8) & 0xFF00);
        Loader_CodeLength |= (Loader_CurrentValue & 0x00FF);

        Loader_SetProcessData();
    } else {
        // If it is the first byte
        Loader_CodeLength = (uint16_t) (Loader_CurrentValue & 0x00FF);

        switch (format) {
            case LENGTH_FORMAT_1B:
                Loader_SetProcessData();
                break;
            case LENGTH_FORMAT_2B:
                Loader_CodeLength |= LENGTH_FORMAT_2B_1ST_BYTE;
                break;
        }
    }
}

uint8_t Loader_ProcessCommandLoadField(void)
{
    if (!Loader_IsTagProcessed()) {
        if (JMC_TAG_FIELD != Loader_CurrentValue) {
            return 0x01;
        }

        Loader_SetProcessData();
    } else {
        // Store id
        Mm_SetU08((uint32_t) &Jmc_Fields[Jmc_CurrentOffsetFields].id,
                Loader_CurrentValue);

        // Increase array of fields offset
        Mm_SetU16((uint32_t) &Jmc_CurrentOffsetFields,
                (uint16_t) (Jmc_CurrentOffsetFields + 1));

        // Decrease number of fields to process
        Loader_FieldsOrMethodsToProcess--;

        Loader_SetProcessTag();
    }

    // If all fields have been processed, next step is process all methods
    if (!Loader_FieldsOrMethodsToProcess) {
        Loader_LoaderState &= ~LOADER_STATE_PROCESS_DATA_LOAD_FIELDS;
        Loader_LoaderState |= LOADER_STATE_PROCESS_DATA_LOAD_METHODS;

        // Set number of methods to process
        Loader_FieldsOrMethodsToProcess =
                Jmc_Classes[Jmc_CurrentOffsetClasses].methods;
    }

    return 0x00;
}

uint8_t Loader_ProcessCommandLoadMethod(void)
{
    if (!Loader_IsTagProcessed()) {
        if (JMC_TAG_METHOD != Loader_CurrentValue) {
            return 0x01;
        }

        Loader_SetProcessLength();
    } else if (!Loader_IslengthProcessed()) {
        Loader_ProcessLength(LENGTH_FORMAT_2B);

        if (Loader_IslengthProcessed()) {
            // Skip ID
            Loader_CodeLength -= 2;

            // Store code size
            Mm_SetU16((uint32_t) &Jmc_Methods[Jmc_CurrentOffsetMethods].size,
                (uint16_t) Loader_CodeLength);

            // Set code offset
            Mm_SetU16((uint32_t)
                    &Jmc_Methods[Jmc_CurrentOffsetMethods].offset,
                    Jmc_CurrentOffsetCode);

            Loader_SetProcessData();
        }
    } else {
        if (JMC_UNDEFINED_1B == Jmc_Methods[Jmc_CurrentOffsetMethods].locals) {
            // Set Locals
            Mm_SetU08((uint32_t) &Jmc_Methods[Jmc_CurrentOffsetMethods].locals,
                    Loader_CurrentValue);
        } else if (JMC_UNDEFINED_1B ==
                Jmc_Methods[Jmc_CurrentOffsetMethods].id) {
            // Set ID
            Mm_SetU08((uint32_t) &Jmc_Methods[Jmc_CurrentOffsetMethods].id,
                    Loader_CurrentValue);
        } else {
            // Store bytecode
            Mm_SetU08((uint32_t) &Jmc_Code[Jmc_CurrentOffsetCode],
                    Loader_CurrentValue);

            // Increase code offset
            Mm_SetU16((uint32_t) &Jmc_CurrentOffsetCode,
                    (uint16_t) (Jmc_CurrentOffsetCode + 1));

            // Decrement bytecode
            Loader_CodeLength--;
        }

        // If all code has been processed...
        if (!Loader_CodeLength) {
            // Increase array of methods offset
            Mm_SetU16((uint32_t) &Jmc_CurrentOffsetMethods,
                    (uint16_t) (Jmc_CurrentOffsetMethods + 1));

            Loader_FieldsOrMethodsToProcess--;
        }
    }

    if (!Loader_FieldsOrMethodsToProcess) {
        // Clear flag
        Loader_LoaderState &= ~LOADER_STATE_PROCESS_DATA_LOAD_METHODS;
        // Send OK
        Loader_SendResponse(LOADER_NO_ERROR);
        // Disable
        Loader_Disable();
    }

    return 0x00;
}

uint8_t Loader_ProcessCommandLoadClass(void)
{
    if (!Loader_IsTagProcessed()) {
        if (Loader_CurrentValue != JMC_TAG_CLASS) {
            return 0x01;
        }

        Loader_SetProcessData();
    } else {
        if (JMC_UNDEFINED_1B == Jmc_Classes[Jmc_CurrentOffsetClasses].fields) {
            Mm_SetU08((uint32_t) &Jmc_Classes[Jmc_CurrentOffsetClasses].fields,
                    Loader_CurrentValue);

            // Store value to use when process all fields
            Loader_FieldsOrMethodsToProcess = Loader_CurrentValue;

            // Store offset
            if (Loader_CurrentValue) {
                Mm_SetU16((uint32_t)
                        &Jmc_Classes[Jmc_CurrentOffsetClasses].fieldsOffset,
                        Jmc_CurrentOffsetFields);
            }
        } else {
            Mm_SetU08((uint32_t) &Jmc_Classes[Jmc_CurrentOffsetClasses].methods,
                    Loader_CurrentValue);

            Loader_LoaderState &= ~LOADER_STATE_PROCESS_DATA_LOAD_CLASS;
            Loader_LoaderState |= LOADER_STATE_PROCESS_DATA_LOAD_FIELDS;

            Loader_SetProcessTag();

            // Store offset
            if (Loader_CurrentValue) {
                Mm_SetU16((uint32_t)
                        &Jmc_Classes[Jmc_CurrentOffsetClasses].methodsOffset,
                        Jmc_CurrentOffsetMethods);
            }
        }
    }

    return 0x00;
}

void Loader_ProcessCommandLoad(void)
{
    uint8_t error = 0x00;

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
            switch (Loader_LoaderState & LOADER_STATE_PROCESS_DATA_LOAD_MASK) {
                case LOADER_STATE_PROCESS_DATA_LOAD_CLASS:
                    error = Loader_ProcessCommandLoadClass();
                    break;
                case LOADER_STATE_PROCESS_DATA_LOAD_FIELDS:
                    error = Loader_ProcessCommandLoadField();
                    break;
                case LOADER_STATE_PROCESS_DATA_LOAD_METHODS:
                    error = Loader_ProcessCommandLoadMethod();
                    break;
                default:
                    error++;
                    break;
            }
    }

    if (0x00 < error) {
        Loader_SendResponse(LOADER_ERROR_WRONG_DATA);
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
                Loader_SendResponse(LOADER_ERROR_CLA_NOT_SUPPORTED);
            }
            break;
        case LOADER_CMD_INS_OFFSET:
            switch (Loader_CurrentValue) {
                case LOADER_CMD_LOAD_INS:
                    Loader_CmdReceived = Loader_CurrentValue;
                    break;
                default:
                    Loader_SendResponse(LOADER_ERROR_INS_NOT_SUPPORTED);
                    break;
            }

            Loader_LoaderState |= LOADER_STATE_PROCESS_DATA;
            break;
    }
}

void Loader_ISR(void)
{
    switch (Loader_LoaderState & LOADER_STATE_PROCESS_MASK) {
        case LOADER_STATE_PROCESS:
            Loader_ProcessCommandHeader();
            break;
        case LOADER_STATE_PROCESS_DATA:
            Loader_ProcessCommandData();
            break;
    }

    Loader_InputOffset++;

    // Stop waiting
    Timer_T0_Stop();
    // Indicates to external device that it can continue
    SerialPort_Send(LOADER_CONTINUE_BYTE);
    // Idle
    Loader_SetToIdle();
    // Enable Serial Port Interrupt
    SerialPort_EnableRx();
}

void Loader_SendResponse(uint16_t error)
{
    // Stop waiting
    Timer_T0_Stop();

    // Send error
    SerialPort_Send((uint8_t) (error >> 8));
    SerialPort_Send((uint8_t) (error));

    // Reset state
    Loader_LoaderState = LOADER_STATE_IDLE;
}

void Loader_Disable(void)
{
    // Set to idle
    Loader_SetToIdle();
    // Mark as disabled
    Mm_SetU08((uint32_t) &Loader_IsLoaderEnabled, LOADER_DISABLED);
}
