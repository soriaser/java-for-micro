#include "Common.h"
#include "Loader.h"

unsigned char Loader_InputArrayPointer = 0x00;

unsigned char Loader_IsLoaderEnabled = 0x00;

volatile unsigned char Loader_InputArray[LOADER_INPUT_ARRAY_MAX_SIZE];

void Loader_ISR(void)
{
    Loader_InputArray[Loader_InputArrayPointer] = RCREG;
    Loader_InputArrayPointer++;

    if (LOADER_INPUT_ARRAY_MAX_SIZE <= Loader_InputArrayPointer) {
        Loader_InputArrayPointer = 0x00;
    }
}
