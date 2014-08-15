#include "Common.h"

#include "Loader.h"
#include "MemoryManagement.h"

const unsigned char Loader_InputArrayPointer = 0x00;

const unsigned char Loader_IsLoaderEnabled = 0x00;

volatile unsigned char Loader_InputArray[LOADER_INPUT_ARRAY_MAX_SIZE];

void Loader_ISR(void)
{
    unsigned char inputArrayPointer =
        Mm_GetByteNVM((unsigned char *) &Loader_InputArrayPointer);

    Loader_InputArray[inputArrayPointer] = RCREG;
    inputArrayPointer++;

    if (LOADER_INPUT_ARRAY_MAX_SIZE <= inputArrayPointer) {
        inputArrayPointer = 0x00;
    }

    Mm_SetByteNVM((unsigned char *) &Loader_InputArrayPointer,
            inputArrayPointer);
}
