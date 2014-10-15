#include "Common.h"

#include "Stack.h"
#include "Heap.h"

uint16_t *Stack_Pointer;
uint16_t *Stack_CurrentPointer;
uint16_t *Stack_BasePointer;

extern void Stack_Init(void)
{
    Stack_Pointer = (uint16_t *) Heap;
    Stack_CurrentPointer = Stack_Pointer - 1;
}

extern void Stack_Push(uint16_t value)
{
    *(++Stack_CurrentPointer) = value;
}
