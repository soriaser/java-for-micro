#include "Common.h"
#include "Heap.h"
#include "JavaClass.h"
#include "Stack.h"
#include "MemoryManagement.h"

uint16_t *Stack_Pointer;
uint16_t *Stack_CurrentPointer;
uint16_t *Stack_BasePointer;

void Stack_Init(void)
{
    Stack_Pointer = (uint16_t *) Heap;
    Stack_CurrentPointer = Stack_Pointer - 1;

    Heap_GetBytes(sizeof(uint16_t) *
            (JavaClass_GetNumberStaticFields() + 1));

    Stack_CurrentPointer += JavaClass_GetNumberStaticFields();
}
